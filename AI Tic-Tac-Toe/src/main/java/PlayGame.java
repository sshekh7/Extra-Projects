import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class PlayGame {
    private static String initial_board;
    private static ArrayList<Node> player_one_moves = new ArrayList<>();
    private static ArrayList<Node> player_two_moves = new ArrayList<>();
    private static int player_one_best_move;
    private static int player_two_best_move;
    private static ArrayList<String> game_play;
    private static ArrayList<Integer> difficulty_levels;
    private static int num_rounds = 1;
    private static ArrayList<Integer> who_won = new ArrayList<>();
    private static int win_draw_lose = -1;   // set to 1 (on X win), set to 2 (on draw), set to 3 (on X lose)

    public static int getWin_draw_lose() {
        return win_draw_lose;
    }

    private static ArrayList<ArrayList<String>> all_games;

    public PlayGame(ArrayList<Integer> user_difficulty, int rounds_choice) throws ExecutionException, InterruptedException {
        difficulty_levels = new ArrayList<>(2);
        difficulty_levels.add(user_difficulty.get(0));
        difficulty_levels.add(user_difficulty.get(1));
        num_rounds = rounds_choice;
        all_games = new ArrayList<ArrayList<String>>(num_rounds);
        who_won = new ArrayList<Integer>(num_rounds);
        game_play = new ArrayList<>();
        initial_board = "b b b b b b b b b";
//        game_play.add(initial_board);
        play_game_now();
    }

    public static ArrayList<Integer> getWho_won() {
        return who_won;
    }

    public static void play_game_now() throws ExecutionException, InterruptedException {
        ExecutorService executorService = Executors.newFixedThreadPool(2);
        Future<ArrayList<Node>> player_one_move;
        Future<ArrayList<Node>> player_two_move;

        for(int i = 0; i < num_rounds; i++){
            System.out.printf("For X: ");
            System.out.println(initial_board);
            player_one_move = executorService.submit(new CalculateMove(initial_board,1, difficulty_levels));
            player_one_moves = player_one_move.get(); // blocking call
            chooseBestMove(1);
            printBestMoves(1);
            temp_print_stuff(player_one_moves);

            System.out.printf("For O: ");
            System.out.println(initial_board);
            player_two_move = executorService.submit(new CalculateMove(initial_board,2, difficulty_levels));
            player_two_moves = player_two_move.get(); // blocking call
            chooseBestMove(2);
            printBestMoves(2);
            temp_print_stuff(player_two_moves);

            while(player_one_best_move != -1){
                if(player_two_move.isDone()){
                    System.out.printf("For X: ");
                    System.out.println(initial_board);
                    player_one_move = executorService.submit(new CalculateMove(initial_board,1, difficulty_levels));
                    player_one_moves = player_one_move.get();
                    chooseBestMove(1);
                    printBestMoves(1);
                    temp_print_stuff(player_one_moves);
                    if(check_end(initial_board, 2)) break;
                }
                if(player_one_move.isDone()){
                    System.out.printf("For O: ");
                    System.out.println(initial_board);
                    player_two_move = executorService.submit(new CalculateMove(initial_board,2, difficulty_levels));
                    player_two_moves = player_two_move.get(); // blocking call
                    chooseBestMove(2);
                    printBestMoves(2);
                    temp_print_stuff(player_two_moves);
                    if(check_end(initial_board, 1)) break;
                }

            }
            all_games.add(game_play);
            who_won.add(win_draw_lose);
            System.out.printf("Win_Draw_Lose: ");
            System.out.println(win_draw_lose);
            initial_board = "b b b b b b b b b";
            game_play = new ArrayList<>();
        }
        executorService.shutdown();
    }

    private static boolean check_end(String instance_initial, int which_player) {
//        if(which_player == 1 && chosen_state.getMinMax() == 10){
//            win_draw_lose = 1;
//            return true;
//        }
//        else if(which_player == 2 && chosen_state.getMinMax() == -10){
//            win_draw_lose = 3;
//            return true;
//        }
//        else if(chosen_state.checkForDraw() == true){
//            win_draw_lose = 2;
//            return true;
//        }
//        return false;
        if(which_player == 1){
            if( (instance_initial.charAt(0) == 'X' && instance_initial.charAt(2) == 'X' && instance_initial.charAt(4) == 'X') ||
                (instance_initial.charAt(6) == 'X' && instance_initial.charAt(8) == 'X' && instance_initial.charAt(10) == 'X') ||
                (instance_initial.charAt(12) == 'X' && instance_initial.charAt(14) == 'X' && instance_initial.charAt(16) == 'X') ||
                (instance_initial.charAt(0) == 'X' && instance_initial.charAt(6) == 'X' && instance_initial.charAt(12) == 'X') ||
                (instance_initial.charAt(2) == 'X' && instance_initial.charAt(8) == 'X' && instance_initial.charAt(14) == 'X') ||
                (instance_initial.charAt(4) == 'X' && instance_initial.charAt(10) == 'X' && instance_initial.charAt(16) == 'X') ||
                (instance_initial.charAt(0) == 'X' && instance_initial.charAt(8) == 'X' && instance_initial.charAt(16) == 'X') ||
                (instance_initial.charAt(4) == 'X' && instance_initial.charAt(8) == 'X' && instance_initial.charAt(12) == 'X')){
                win_draw_lose = 1;
                return true;
            } else if(!instance_initial.contains("b") && win_draw_lose > 0){
                win_draw_lose = 2;
                return true;
            }
        }
        else if(which_player == 2){
            if((instance_initial.charAt(0) == 'O' && instance_initial.charAt(2) == 'O' && instance_initial.charAt(4) == 'O') ||
                (instance_initial.charAt(6) == 'O' && instance_initial.charAt(8) == 'O' && instance_initial.charAt(10) == 'O') ||
                (instance_initial.charAt(12) == 'O' && instance_initial.charAt(14) == 'O' && instance_initial.charAt(16) == 'O') ||
                (instance_initial.charAt(0) == 'O' && instance_initial.charAt(6) == 'O' && instance_initial.charAt(12) == 'O') ||
                (instance_initial.charAt(2) == 'O' && instance_initial.charAt(8) == 'O' && instance_initial.charAt(14) == 'O') ||
                (instance_initial.charAt(4) == 'O' && instance_initial.charAt(10) == 'O' && instance_initial.charAt(16) == 'O') ||
                (instance_initial.charAt(0) == 'O' && instance_initial.charAt(8) == 'O' && instance_initial.charAt(16) == 'O') ||
                (instance_initial.charAt(4) == 'O' && instance_initial.charAt(8) == 'O' && instance_initial.charAt(12) == 'O')){
                win_draw_lose = 3;
                return true;
            } else if(!instance_initial.contains("b") && win_draw_lose > 0){
                win_draw_lose = 2;
                return true;
            }
        }

        win_draw_lose = 0;
        return false;
    }

    private static void temp_print_stuff(ArrayList<Node> print){
        for(int i = 0; i < print.size(); i++){
//            System.out.printf("Size: ");
//            System.out.println(print.size());
            Node temp = print.get(i);
            System.out.printf("Node: ");
            System.out.println(Arrays.toString(temp.getInitStateString()));
            System.out.println(temp.getMovedTo());
        }
//        System.out.println(Arrays.toString(print.toArray()));

    }

    private static void printBestMoves(int which_player)
    {
        Node temp;
        int limit;
        if(which_player == 1) limit = player_one_moves.size(); else limit = player_two_moves.size();
        for(int x = 0; x < limit; x++)
        {
            if(which_player == 1) temp = player_one_moves.get(x); else temp = player_two_moves.get(x);

            if(which_player == 1 && x == player_one_best_move){

                initial_board = Arrays.toString(temp.getInitStateString());
            }
            else if(which_player == 2 && x == player_two_best_move){

                initial_board = Arrays.toString(temp.getInitStateString());
            }
        }

        StringBuilder temp_string = new StringBuilder();
        for(int i = 0; i < initial_board.length();i++){
            if(initial_board.charAt(i) == 'O' || initial_board.charAt(i) == 'X' || initial_board.charAt(i) == 'b'){
                temp_string.append(initial_board.charAt(i)).append(" ");
            }
        }
        initial_board = temp_string.toString();
        game_play.add(initial_board);
    }

    private static void chooseBestMove(int which_player){
        Random rand = new Random();
//        if(which_player == 1){
//            if(player_one_moves.size() != 0) player_one_best_move = rand.nextInt(player_one_moves.size());
//            else player_one_best_move = -1;
//        }
//        else if (which_player == 2){
//            if(player_two_moves.size() != 0) player_two_best_move = rand.nextInt(player_two_moves.size());
//            else player_two_best_move = -1;
//        }

        if(which_player == 1){
            ArrayList<Integer> temp_array = new ArrayList<>();
            for(int i = 0; i < player_one_moves.size(); i++){
                Node temp = player_one_moves.get(i);
                if(temp.getMinMax() == 10){
                    temp_array.add(i);
                }
            }
            if(temp_array.isEmpty()){
                for(int i = 0; i < player_one_moves.size(); i++){
                    Node temp = player_one_moves.get(i);
                    if(temp.getMinMax() == 0){
                        temp_array.add(i);
                    }
                }
            }
            if(temp_array.isEmpty()) player_one_best_move = -1;
            else player_one_best_move = temp_array.get(rand.nextInt(temp_array.size()));
        }
        else if(which_player == 2){
            ArrayList<Integer> temp_array = new ArrayList<>();
            for(int i = 0; i < player_two_moves.size(); i++){
                Node temp = player_two_moves.get(i);
                if(temp.getMinMax() == -10){
                    temp_array.add(i);
                }
            }
            if(temp_array.isEmpty()){
                for(int i = 0; i < player_two_moves.size(); i++){
                    Node temp = player_two_moves.get(i);
                    if(temp.getMinMax() == 0){
                        temp_array.add(i);
                    }
                }
            }
            if(temp_array.isEmpty()) player_two_best_move = -1;
            else player_two_best_move = temp_array.get(rand.nextInt(temp_array.size()));
        }
    }

//    public static ArrayList<String> getGame_play() {
//        return game_play;
//    }

    public static ArrayList<ArrayList<String>> getAll_games() {
        return all_games;
    }
}

