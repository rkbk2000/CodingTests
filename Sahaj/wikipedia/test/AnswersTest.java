package test;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;

import org.junit.jupiter.api.Test;

import wiki.Answers;

class AnswersTest {

	@Test
	final void testAnswersForNullInput() {
		Answers answers = new Answers(null);
		ArrayList<String> elements = answers.getElements();
		assertEquals(0, elements.size());
	}

	final void testAnswersFor5Answers() {
		Answers answers = new Answers("a;b;c;d;e");
		String[] expected = { "a", "b", "c", "d", "e" };
		checkElements(expected, answers);
	}

	final void testAnswersFor1Answer() {
		Answers answers = new Answers("a");
		String[] expected = { "a" };
		checkElements(expected, answers);
	}

	final void checkElements(String[] expected, Answers answers) {
		ArrayList<String> elements = answers.getElements();
		assertEquals(expected.length, elements.size());
		for (int i = 0; i < answers.getElements().size(); ++i) {
			assertEquals(expected[i], elements.get(i));
		}
	}

}
