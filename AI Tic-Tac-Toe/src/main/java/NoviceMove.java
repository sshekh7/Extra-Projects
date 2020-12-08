import java.util.ArrayList;

public class NoviceMove {
    private String[] init_board;

    private ArrayList<Node> movesList;

    private String initial_stage = "";
    private int player;

    public ArrayList<Node> getMovesList() {
        return movesList;
    }

    public NoviceMove(String game_instance, int which_player) {
        this.initial_stage = game_instance;
        init_board = getBoard();
        movesList = new ArrayList<>();
        player = which_player;
        set_moves_list();
    }

    private void set_moves_list() {
        int move_to = -1;
        for(int i = 0; i < init_board.length; i++){
            if(init_board[i].charAt(0) == 'b'){
                move_to = i;
                if(player == 1){
                    init_board[i] = init_board[i].replace('b', 'X');
                } else init_board[i] = init_board[i].replace('b', 'O');

                break;
            }
        }

        if(move_to != -1){
            Node temp_node = new Node(init_board,move_to+1);
            if(player == 1) temp_node.setMinMax(10); else temp_node.setMinMax(-10);
            movesList.add(temp_node);
        }

    }

    private String[] getBoard()
    {
        String puzzle;
        String[] puzzleParsed;
        String delim = "[ ]+";
        puzzle = initial_stage;				//scan in string
        puzzleParsed = puzzle.split(delim);
        return puzzleParsed;
    }
}
