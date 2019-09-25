package wiki;

import java.io.IOException;
import java.io.InputStream;
import java.util.Scanner;

public class InputParser {

	public static final int MAX_LINES_PER_TEST = 7;
	public static final int PARA_INDEX = 0;
	public static final int QUESTION_START = 1;
	public static final int QUESTION_END = 5;
	public static final int ANSWERS_INDEX = 6;

	String[] lines = new String[MAX_LINES_PER_TEST];
	private InputStream fileStream_ = null;

	public InputParser(InputStream in) {
		fileStream_ = in;
		try {
			parse();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private final String[] parse() throws IOException {
		Scanner fileScanner = null;

		fileScanner = new Scanner(fileStream_);

		for (int i = 0; i < MAX_LINES_PER_TEST; ++i) {
			String line = fileScanner.nextLine();
			lines[i] = line;
		}
		fileScanner.close();
		return lines;
	}

	public final Paragraph getParagraph() {
		return new Paragraph(lines[PARA_INDEX]);
	}

	public final Questions getQuestions() {
		Questions questions = new Questions();
		for (int qidx = QUESTION_START; qidx <= QUESTION_END; ++qidx) {
			questions.addQuestion(lines[qidx]);
		}
		return questions;
	}

	public final Answers getAnswers() {
		Answers answers = new Answers(lines[ANSWERS_INDEX]);
		return answers;
	}
}
