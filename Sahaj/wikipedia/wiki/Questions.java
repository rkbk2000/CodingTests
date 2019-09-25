package wiki;

import java.util.ArrayList;

public class Questions {

	public static int MAX_QUESTIONS = 5;
	private ArrayList<String> questions_ = new ArrayList<String>();

	public boolean addQuestion(String question) {
		boolean rc = false;
		if (questions_.size() < MAX_QUESTIONS) {
			questions_.add(question.replace("?", ""));
		}
		return rc;
	}

	public ArrayList<String> getElements() {
		return questions_;
	}

}
