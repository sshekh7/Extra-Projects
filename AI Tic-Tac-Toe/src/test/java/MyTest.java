import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import org.junit.jupiter.api.DisplayName;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import java.util.ArrayList;

class MyTest {

	@Test
	void state_list_test() {
		String move = "b b b b b b b b b";
		AI_MinMax new_move = new AI_MinMax(move, 1);
		assertEquals(9, new_move.getMovesList().size());
	}

	@Test
	void state_list_test2() {
		String move = "b X b X b b O b O";
		AI_MinMax new_move = new AI_MinMax(move, 1);
		assertEquals(5, new_move.getMovesList().size());
	}

	@Test
	void state_list_test3() {
		String move = "O X O X O X O X O";
		AI_MinMax new_move = new AI_MinMax(move, 1);
		assertEquals(0, new_move.getMovesList().size());
	}

	@Test
	void move_to_test() {
		String move = "O X O X O X b b b";
		AI_MinMax new_move = new AI_MinMax(move, 1);
		ArrayList<Node> temp = new ArrayList<>();
		temp = new_move.getMovesList();
		assertEquals(3, new_move.getMovesList().size());
		assertEquals(-10, temp.get(0).getMinMax());
	}

	@Test
	void move_to_test2() {
		String move = "O X O X O X O O b";
		AI_MinMax new_move = new AI_MinMax(move, 1);
		ArrayList<Node> temp = new ArrayList<>();
		temp = new_move.getMovesList();
		assertEquals(1, new_move.getMovesList().size());
		assertEquals(0, temp.get(0).getMinMax());
	}

	@Test
	void move_to_test3() {
		String move = "X X b b b b b b b";
		AI_MinMax new_move = new AI_MinMax(move, 1);
		ArrayList<Node> temp = new ArrayList<>();
		temp = new_move.getMovesList();
		assertEquals(7, new_move.getMovesList().size());
		assertEquals(10, temp.get(0).getMinMax());
	}

	@Test
	void node_test(){
		String[] temp_array = {"b", "b", "b", "b", "b", "b", "b", "b", "b"};

		Node temp_node = new Node(temp_array,1);

		assertEquals(1, temp_node.getMovedTo());

	}

	@Test
	void node_test2(){
		String[] temp_array = {"b", "b", "b", "b", "b", "b", "b", "b", "b"};

		Node temp_node = new Node(temp_array,1);

		assertEquals(-1, temp_node.getMinMax());

	}

	@Test
	void node_test3(){
		String[] temp_array = {"b", "b", "b", "b", "b", "b", "b", "b", "b"};

		Node temp_node = new Node(temp_array,1);

		assertArrayEquals(temp_array,temp_node.getInitStateString());

	}

	@Test
	void min_max_test(){
		String[] temp_array = {"X", "b", "b", "b", "b", "b", "b", "b", "b"};
		MinMax temp_min_max = new MinMax(temp_array,2);
		assertEquals(8, temp_min_max.findMoves(2).size());
	}

}
