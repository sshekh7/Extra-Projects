import java.util.ArrayList;
import java.util.Scanner;

/**
 * This class is used to read in a state of a tic tac toe board. It creates a MinMax object and passes the state to it. What returns is a list 
 * of possible moves for the player X that have been given min/max values by the method findMoves. The moves that can result in a win or a 
 * tie for X are printed out with the method printBestMoves()
 * 
 * @author Mark Hallenbeck
 *
 * Copyright© 2014, Mark Hallenbeck, All Rights Reservered.
 *
 */
public class AI_MinMax {

	private String[] init_board;

	private ArrayList<Node> movesList;

	private String initial_stage = "";


	AI_MinMax(String game_instance, int which_player)
	{
		this.initial_stage = game_instance;
		init_board = getBoard();
		MinMax sendIn_InitState = new MinMax(init_board, which_player);
		movesList = sendIn_InitState.findMoves(which_player);
	}

	public ArrayList<Node> getMovesList() {
		return movesList;
	}

	/**
	 * reads in a string from user and parses the individual letters into a string array
	 * @return String[]
	 */
	private String[] getBoard()
	{
			String puzzle;
			String[] puzzleParsed;
			String delim = "[ ]+";
			puzzle = initial_stage;				//scan in string
			puzzleParsed = puzzle.split(delim);
			return puzzleParsed;
	}
	
	/**
	 * goes through a node list and prints out the moves with the best result for player X
	 * checks the min/max function of each state and only recommends a path that leads to a win or tie
	 */
	private void printBestMoves()
	{
		System.out.print("\n\nThe moves list is: < ");
		
		for(int x = 0; x < movesList.size(); x++)
		{
			Node temp = movesList.get(x);
			
			if(temp.getMinMax() == 10 || temp.getMinMax() == 0)
			{
				System.out.print(temp.getMovedTo() + " ");
			}
		}
		
		System.out.print(">");
	}

}
