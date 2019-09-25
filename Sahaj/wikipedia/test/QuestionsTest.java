package test;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;

import org.junit.jupiter.api.Test;

import wiki.Questions;

class QuestionsTest {

	@Test
	final void testQuestionsDefaultConstuctions() {
		Questions questions = new Questions();
		ArrayList<String> elements = questions.getElements();
		assertEquals(0, elements.size());
	}

	@Test
	final void testQuestions1Question() {
		Questions questions = new Questions();
		String qStr = "What is your name?";
		questions.addQuestion(qStr);

		ArrayList<String> elements = questions.getElements();
		assertEquals(1, elements.size());

		String expected = "What is your name";
		assertEquals(expected, elements.get(0));
	}

	@Test
	final void testQuestions5() {
		Questions questions = new Questions();
		String inputs[] = { "a?", "b?", "c?", "d?", "e?" };

		addQuestions(questions, inputs);

		String expected[] = { "a", "b", "c", "d", "e" };
		assertEquals(5, questions.getElements().size());
		checkQuestions(questions, expected);
	}

	@Test
	final void testQuestionsMrethan5() {
		Questions questions = new Questions();
		String inputs[] = { "a?", "b?", "c?", "d?", "e?", "f?" };

		addQuestions(questions, inputs);

		String expected[] = { "a", "b", "c", "d", "e" };
		assertEquals(5, questions.getElements().size());
		checkQuestions(questions, expected);
	}

	void addQuestions(Questions questions, String inputs[]) {
		for (String q : inputs) {
			questions.addQuestion(q);
		}
	}

	void checkQuestions(Questions questions, String expected[]) {
		for (int qIdx = 0; qIdx < expected.length; ++qIdx) {
			assertEquals(expected[qIdx], questions.getElements().get(qIdx));
		}
	}
}
