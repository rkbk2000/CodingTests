package wiki;

import java.util.ArrayList;

public class Answers {

	private ArrayList<String> answers_;
	public final static String ANSWER_DELIMITER = ";";

	public Answers(String answers) {
		answers_ = StringScanner.scanString(answers, ANSWER_DELIMITER);
	}

	public ArrayList<String> getElements() {
		return answers_;
	}
}
