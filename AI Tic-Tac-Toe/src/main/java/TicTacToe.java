import javafx.animation.PauseTransition;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.ExecutionException;

public class TicTacToe extends Application implements EventHandler {

    Button one = new Button(null);
    Button two = new Button(null);
    Button three = new Button(null);
    Button four = new Button(null);
    Button five = new Button(null);
    Button six = new Button(null);
    Button seven = new Button(null);
    Button eight = new Button(null);
    Button nine = new Button(null);
    Button start_game = new Button("Start");
    Text player_one = new Text();
    Text player_two = new Text();

    int x_score = 0;
    int o_score = 0;

    Stage specific_stage;
    ArrayList<Integer> who_won = new ArrayList<>();

    static ArrayList<ArrayList<String>> game_play = new ArrayList<ArrayList<String>>();
    int numRounds  = 1;
    ArrayList<Integer> user_difficulty = new ArrayList<>();

    VBox board;

    HashMap<String, Integer> sceneMap;
    public static void main(String[] args) {
        launch(args);
    }
    @Override
    public void start(Stage primaryStage) throws Exception {
        user_difficulty.add(1);
        user_difficulty.add(1);
        primaryStage.setTitle("TicTacToe Master");
        welcome_screen(primaryStage);
    }

    private void game_score(Stage stage, int j) {
        ImageView logo = new ImageView();
        logo.setImage(new Image("logo.png"));
        logo.setFitHeight(250);
        logo.setFitWidth(150);
//        setBoard();
        ArrayList<String> display_text = new ArrayList<>();
        display_text.add("X Wins!");
        display_text.add("O Wins!");
        display_text.add("Match Draw :-|");

        Text win_text = new Text();
        if(who_won.get(j) == 1) win_text.setText(display_text.get(0));
        else if(who_won.get(j) == 3) win_text.setText(display_text.get(1));
        else win_text.setText(display_text.get(2));
        win_text.setFont(Font.font("verdana", FontPosture.REGULAR, 20));
        HBox logo_display = new HBox(logo);
        logo_display.setAlignment(Pos.CENTER);


        Text start_text = new Text();
        start_text.setFont(Font.font("verdana", FontPosture.REGULAR, 15));

        HBox start_text_display = new HBox(start_text);
        start_text_display.setAlignment(Pos.CENTER);

        final int[] i = {6};
        final String[] text = {"Closing in 5 seconds"};
        start_text.setText(text[0]);
        Timer t = new Timer();
        t.schedule(new TimerTask() {
            @Override
            public void run() {
                i[0] = i[0] - 1;
                text[0] = "Closing in " + i[0] + " seconds";
                start_text.setText(text[0]);
                if(i[0] == 0) t.cancel();
            }
        }, 0, 1000);

        HBox board_box = new HBox(board);
        board_box.setAlignment(Pos.CENTER);
        VBox main_screen = new VBox(logo_display,board_box,win_text,start_text_display);
        main_screen.setSpacing(50);
        main_screen.setBackground(new Background(new BackgroundFill(Color.LIGHTSTEELBLUE, null, null)));
        main_screen.setAlignment(Pos.CENTER);
        Scene scene = new Scene(main_screen, 700,700);
        stage.setScene(scene);
        stage.show();

        PauseTransition delay = new PauseTransition(Duration.seconds(5));
        delay.setOnFinished( event -> game_screen(stage));
        delay.play();
    }

    private void game_screen(Stage stage) {
        specific_stage = new Stage();
        specific_stage = stage;
        Text logo_text = new Text("Tic-Tac-Toe Master");
        logo_text.setFont(Font.font("verdana", FontPosture.REGULAR, 30));

        Button game_instructions = new Button("Rules");
        game_instructions.setId("rules");
        game_instructions.setOnAction(this);
        game_instructions.setStyle("-fx-background-color: #ffffff; ");
        game_instructions.setFont(Font.font("verdana", FontPosture.REGULAR, 14));

        Button game_rules = new Button("Instructions");
        game_rules.setId("instructions");
        game_rules.setOnAction(e->instructionsAlert());
        game_rules.setStyle("-fx-background-color: #ffffff; ");
        game_rules.setFont(Font.font("verdana", FontPosture.REGULAR, 14));

        HBox instructions_align = new HBox(game_instructions, game_rules);
        instructions_align.setSpacing(10);
        instructions_align.setAlignment(Pos.CENTER);

        VBox header_text = new VBox(logo_text, instructions_align);
        header_text.setSpacing(15);
        HBox header = new HBox(header_text);
        header.setAlignment(Pos.CENTER);

        String[] difficulty_levels = {"Novice", "Advanced","Expert"};
        String[] consecutive_rounds = {"1","2","3","4","5","6","7","8","9","10"};

        Text txt1 = new Text();
        txt1.setText("Difficulty \nPlayer 1");
        txt1.setFont(Font.font("verdana", FontPosture.REGULAR, 13));

        Text txt1_1 = new Text();
        txt1_1.setText("Difficulty \nPlayer 2");
        txt1_1.setFont(Font.font("verdana", FontPosture.REGULAR, 13));

        Text txt2 = new Text();
        txt2.setText("Rounds");
        txt2.setFont(Font.font("verdana", FontPosture.REGULAR, 13));

        ChoiceBox game_difficulty = new ChoiceBox(FXCollections.observableArrayList(difficulty_levels));
        game_difficulty.setId("difficulty_selection");
        game_difficulty.setOnAction(this);
        game_difficulty.setStyle("-fx-background-color: #ffffff; ");
        game_difficulty.setValue("Novice");

        ChoiceBox game_difficulty1_1 = new ChoiceBox(FXCollections.observableArrayList(difficulty_levels));
        game_difficulty1_1.setId("difficulty_selection1_1");
        game_difficulty1_1.setOnAction(this);
        game_difficulty1_1.setStyle("-fx-background-color: #ffffff; ");
        game_difficulty1_1.setValue("Novice");

        ChoiceBox rounds = new ChoiceBox(FXCollections.observableArrayList(consecutive_rounds));
        rounds.setId("rounds_selection");
        rounds.setOnAction(this);
        rounds.setStyle("-fx-background-color: #ffffff; ");
        rounds.setValue("1");


        VBox difficulty_select = new VBox(txt1, game_difficulty);
        difficulty_select.setSpacing(7);

        VBox difficulty_select1_1 = new VBox(txt1_1, game_difficulty1_1);
        difficulty_select1_1.setSpacing(7);

        VBox round_select = new VBox(txt2, rounds);
        round_select.setSpacing(7);

        HBox two_players = new HBox(difficulty_select, difficulty_select1_1);
        two_players.setSpacing(10);

        HBox buttons_array = new HBox(two_players, round_select);
        buttons_array.setSpacing(300);
        buttons_array.setAlignment(Pos.CENTER);

        Text txt3 = new Text();
        txt3.setText("Scores");
        txt3.setFont(Font.font("verdana", FontPosture.REGULAR, 17));

        HBox label_align = new HBox(txt3);
        label_align.setAlignment(Pos.CENTER);


        player_one.setText("Player 1: " + x_score);
        player_one.setFont(Font.font("verdana", FontPosture.REGULAR, 13));
//        x_score.setFont(Font.font("verdana", FontPosture.REGULAR, 13));

        HBox player_one_score = new HBox(player_one);
        player_one_score.setAlignment(Pos.CENTER);



        player_two.setText("Player 2: " + o_score);
        player_two.setFont(Font.font("verdana", FontPosture.REGULAR, 13));


        HBox player_two_score = new HBox(player_two);
        player_two_score.setAlignment(Pos.CENTER);

        VBox score = new VBox(label_align, player_one_score, player_two_score);
        score.setSpacing(5);
        score.setAlignment(Pos.CENTER);


        start_game.setId("start_game");
        start_game.setOnAction(this);
        start_game.setStyle("-fx-background-color: #ffffff; ");
        start_game.setFont(Font.font("verdana", FontPosture.REGULAR, 14));
        HBox start = new HBox(start_game);
        start.setAlignment(Pos.CENTER);
        Button exit_button = new Button("Exit");
        exit_button.setStyle("-fx-background-color: #ffffff; ");
        exit_button.setOnAction(e -> System.exit(0));
        HBox exit_align = new HBox(exit_button);
        exit_align.setAlignment(Pos.CENTER);
        exit_button.setFont(Font.font("verdana", FontPosture.REGULAR, 13));
        setBoard();
        HBox board_box = new HBox(board);
        board_box.setAlignment(Pos.CENTER);
        VBox main_screen = new VBox(header, buttons_array, start, board_box, score, exit_align);
        main_screen.setBackground(new Background(new BackgroundFill(Color.LIGHTSTEELBLUE, null, null)));
        main_screen.setSpacing(45);
        Scene scene = new Scene(main_screen, 700,700);
        stage.setScene(scene);
        stage.show();
    }

    private void welcome_screen(Stage stage) {

        ImageView logo = new ImageView();
        logo.setImage(new Image("logo.png"));
        logo.setFitHeight(350);
        logo.setFitWidth(250);

        HBox logo_display = new HBox(logo);
        logo_display.setAlignment(Pos.CENTER);


        Text start_text = new Text();
        start_text.setFont(Font.font("verdana", FontPosture.REGULAR, 15));

        HBox start_text_display = new HBox(start_text);
        start_text_display.setAlignment(Pos.CENTER);

        final int[] i = {6};
        final String[] text = {"Starting in 5 seconds"};
        start_text.setText(text[0]);
        Timer t = new Timer();
        t.schedule(new TimerTask() {
            @Override
            public void run() {
                i[0] = i[0] - 1;
                text[0] = "Starting in " + i[0] + " seconds";
                start_text.setText(text[0]);
                if(i[0] == 0) t.cancel();
            }
        }, 0, 1000);

        VBox main_screen = new VBox(logo_display, start_text_display);
        main_screen.setSpacing(50);
        main_screen.setBackground(new Background(new BackgroundFill(Color.LIGHTSTEELBLUE, null, null)));
        main_screen.setAlignment(Pos.CENTER);
        Scene scene = new Scene(main_screen, 700,700);
        stage.setScene(scene);
        stage.show();

        PauseTransition delay = new PauseTransition(Duration.seconds(5));
        delay.setOnFinished( event -> game_screen(stage));
        delay.play();
    }

    private void setBoard(){

        one.setFont(Font.font("verdana", FontPosture.REGULAR, 23));
        one.setStyle("-fx-background-color: #ffffff; ");
        one.setMinWidth(52.0);
        one.setPrefWidth(52.0);
        one.setMaxWidth(52.0);

        two.setFont(Font.font("verdana", FontPosture.REGULAR, 23));
        two.setStyle("-fx-background-color: #ffffff; ");
        two.setMinWidth(52.0);
        two.setPrefWidth(52.0);
        two.setMaxWidth(52.0);

        three.setFont(Font.font("verdana", FontPosture.REGULAR, 23));
        three.setStyle("-fx-background-color: #ffffff; ");
        three.setMinWidth(52.0);
        three.setPrefWidth(52.0);
        three.setMaxWidth(52.0);

        four.setFont(Font.font("verdana", FontPosture.REGULAR, 23));
        four.setStyle("-fx-background-color: #ffffff; ");
        four.setMinWidth(52.0);
        four.setPrefWidth(52.0);
        four.setMaxWidth(52.0);

        five.setFont(Font.font("verdana", FontPosture.REGULAR, 23));
        five.setStyle("-fx-background-color: #ffffff; ");
        five.setMinWidth(52.0);
        five.setPrefWidth(52.0);
        five.setMaxWidth(52.0);

        six.setFont(Font.font("verdana", FontPosture.REGULAR, 23));
        six.setStyle("-fx-background-color: #ffffff; ");
        six.setMinWidth(52.0);
        six.setPrefWidth(52.0);
        six.setMaxWidth(52.0);

        seven.setFont(Font.font("verdana", FontPosture.REGULAR, 23));
        seven.setStyle("-fx-background-color: #ffffff; ");
        seven.setMinWidth(52.0);
        seven.setPrefWidth(52.0);
        seven.setMaxWidth(52.0);

        eight.setFont(Font.font("verdana", FontPosture.REGULAR, 23));
        eight.setStyle("-fx-background-color: #ffffff; ");
        eight.setMinWidth(52.0);
        eight.setPrefWidth(52.0);
        eight.setMaxWidth(52.0);

        nine.setFont(Font.font("verdana", FontPosture.REGULAR, 23));
        nine.setStyle("-fx-background-color: #ffffff; ");
        nine.setMinWidth(52.0);
        nine.setPrefWidth(52.0);
        nine.setMaxWidth(52.0);

        HBox first_line_text = new HBox(one, two, three);
        HBox second_line_text = new HBox(four, five, six);
        HBox third_line_text = new HBox(seven, eight, nine);

        first_line_text.setSpacing(5);
        second_line_text.setSpacing(5);
        third_line_text.setSpacing(5);

        VBox box_text = new VBox(first_line_text, second_line_text, third_line_text);
        box_text.setSpacing(5);
        board = new VBox(box_text);
    }

    public void resultsAlert() {
        String output_text = "1. The game is played on a grid that's 3 squares by 3 squares.\n" +
                "2. You are X, your friend (or the computer in this case) is O. Players take turns putting their marks in empty squares.\n" +
                "3. The first player to get 3 of her marks in a row (up, down, across, or diagonally) is the winner.\n" +
                "4. When all 9 squares are full, the game is over. If no player has 3 marks in a row, the game ends in a tie.";
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Rules");
        alert.setContentText(output_text);
        alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
        Image image = new Image("alert.png");
        ImageView imageView = new ImageView(image);
        alert.setGraphic(imageView);
        alert.show();
    }

    public void instructionsAlert() {
        String output_text = "How to play\n 1. Click on 'Rules' button to checkout official rules of the game. \n" +
                " 2. Choose difficulty level of the game from the 'Difficulty' selection menu. \n" +
                " 3. Click 'Start' button to start playing against the computer opponent. \n" +
                " 4. To exit form the game, click exit button.";
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Rules");
        alert.setContentText(output_text);
        alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
        Image image = new Image("alert.png");
        ImageView imageView = new ImageView(image);
        alert.setGraphic(imageView);
        alert.show();
    }

    public void display_game(int j){
        // change GUI
        int limit;
        if(who_won.get(j) == 1 || who_won.get(j) == 3){
            limit = game_play.get(j).size()-2;
        } else limit = game_play.get(j).size()-1;
        System.out.printf("J's value: ");
        System.out.println(j);
        System.out.println(game_play.get(j));
        final int[] i = {0};
        final String[] text = {"", "", "", "", "", "", "", "", ""};
        one.setText(null);
        two.setText(null);
        three.setText(null);
        four.setText(null);
        five.setText(null);
        six.setText(null);
        seven.setText(null);
        eight.setText(null);
        nine.setText(null);
        Timer t = new Timer();
        t.schedule(new TimerTask() {
            @Override
            public void run() {
                if(i[0] == limit) {
                    t.cancel();
                    Platform.runLater(new Runnable() {
                        @Override
                        public void run() {
                            PauseTransition delay = new PauseTransition(Duration.seconds(1));
//                            delay.setOnFinished( event -> game_score(specific_stage));
                            delay.setOnFinished(new EventHandler<ActionEvent>() {
                                @Override
                                public void handle(ActionEvent actionEvent) {
                                    game_score(specific_stage, j);
                                    if(who_won.get(j) == 1){
                                        x_score++;
                                        player_one.setText("Player 1: " + x_score);
                                    }
                                    else if(who_won.get(j) == 3){
                                        o_score++;
                                        player_two.setText("Player 2: " + o_score);
                                    }
                                }
                            });
                            delay.play();

                            if(game_play.size() > j+1) {
                                PauseTransition delay2 = new PauseTransition(Duration.seconds(7));
                                delay2.setOnFinished( event -> display_game(j+1));
                                delay2.play();
                            } else start_game.setDisable(false);
                        }
                    });
                }
                text[0] = String.valueOf(game_play.get(j).get(i[0]).charAt(0)) ;
                text[1] = String.valueOf(game_play.get(j).get(i[0]).charAt(2));
                text[2] = String.valueOf(game_play.get(j).get(i[0]).charAt(4));
                text[3] = String.valueOf(game_play.get(j).get(i[0]).charAt(6));
                text[4] = String.valueOf(game_play.get(j).get(i[0]).charAt(8));
                text[5] = String.valueOf(game_play.get(j).get(i[0]).charAt(10));
                text[6] = String.valueOf(game_play.get(j).get(i[0]).charAt(12));
                text[7] = String.valueOf(game_play.get(j).get(i[0]).charAt(14));
                text[8] = String.valueOf(game_play.get(j).get(i[0]).charAt(16));
                Platform.runLater(new Runnable() {
                    @Override
                    public void run() {
                        if(text[0].charAt(0) == 'b') one.setText(null); else one.setText(text[0]);
                        if(text[1].charAt(0) == 'b') two.setText(null); else two.setText(text[1]);
                        if(text[2].charAt(0) == 'b') three.setText(null); else three.setText(text[2]);
                        if(text[3].charAt(0) == 'b') four.setText(null); else four.setText(text[3]);
                        if(text[4].charAt(0) == 'b') five.setText(null); else five.setText(text[4]);
                        if(text[5].charAt(0) == 'b') six.setText(null); else six.setText(text[5]);
                        if(text[6].charAt(0) == 'b') seven.setText(null); else seven.setText(text[6]);
                        if(text[7].charAt(0) == 'b') eight.setText(null); else eight.setText(text[7]);
                        if(text[8].charAt(0) == 'b') nine.setText(null); else nine.setText(text[8]);
                    }
                });
                i[0] = i[0] + 1;
            }
        }, 0, 1500);

        System.out.println("Done");
    }


    @Override
    public void handle(Event event) {
        if(event.getSource() instanceof Button && ((Button) event.getSource()).getId().equals("rules")){
            resultsAlert();
        }

        if(event.getSource() instanceof ChoiceBox && ((ChoiceBox)event.getSource()).getId() == "rounds_selection"){
            numRounds = Integer.parseInt(((ChoiceBox)event.getSource()).getValue().toString());
        }
        if(event.getSource() instanceof ChoiceBox && ((ChoiceBox)event.getSource()).getId() == "difficulty_selection"){
            String user_choice = ((ChoiceBox) event.getSource()).getValue().toString();
            if(user_choice.equals("Novice")){
                user_difficulty.set(0,1);
            }
            else if(user_choice.equals("Advanced")){
                user_difficulty.set(0,2);
            }
            if(user_choice.equals("Expert")){
                user_difficulty.set(0,3);
            }
        }
        if(event.getSource() instanceof ChoiceBox && ((ChoiceBox)event.getSource()).getId() == "difficulty_selection1_1"){
            String user_choice = ((ChoiceBox) event.getSource()).getValue().toString();
            if(user_choice.equals("Novice")){
                user_difficulty.set(1,1);
            }
            else if(user_choice.equals("Advanced")){
                user_difficulty.set(1,2);
            }
            if(user_choice.equals("Expert")){
                user_difficulty.set(1,3);
            }
        }

        if(event.getSource() instanceof Button && ((Button) event.getSource()).getId().equals("start_game")){
            start_game.setDisable(true);
            try {
                PlayGame one_move = new PlayGame(user_difficulty, numRounds);
                game_play = one_move.getAll_games();
                who_won = new ArrayList<>();
                who_won = one_move.getWho_won();
                System.out.printf("who_won_array: ");
                System.out.println(who_won);
                System.out.println(game_play);
            } catch (ExecutionException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            display_game(0);
        }

    }
}