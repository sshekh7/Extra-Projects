import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.concurrent.Callable;

public class CalculateMove implements Callable<ArrayList<Node>> {
    String calculatedMove;
    int which_player;
    ArrayList<Integer> player_difficulty;
    public CalculateMove(String gameInstance, int player, ArrayList<Integer> difficulty) {
        calculatedMove = gameInstance;
        which_player = player;
        player_difficulty = new ArrayList<>(2);
        player_difficulty.add(difficulty.get(0));
        player_difficulty.add(difficulty.get(1));
    }

    @Override
    public ArrayList<Node> call() throws Exception {
        ArrayList<Node> returnNode = new ArrayList<>();
        if(player_difficulty.get(which_player-1) == 3){
            AI_MinMax new_move = new AI_MinMax(calculatedMove,which_player);
            returnNode = new_move.getMovesList();
        }
        else if(player_difficulty.get(which_player-1) == 2){
            AdvancedMove sample = new AdvancedMove(calculatedMove,which_player);
            returnNode = sample.getMovesList();
        }
        else if(player_difficulty.get(which_player-1) == 1){
            NoviceMove sample = new NoviceMove(calculatedMove,which_player);
            returnNode = sample.getMovesList();
        }
        return returnNode;
    }

    private String[] getBoard(String initial_stage)
    {
        String puzzle;
        String[] puzzleParsed;
        String delim = "[ ]+";
        puzzle = initial_stage;				//scan in string
        puzzleParsed = puzzle.split(delim);
        return puzzleParsed;
    }
}
