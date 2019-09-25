package test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import wiki.Paragraph;

class ParagraphTest {

	@Test
	final void testForNull() {
		Paragraph para = new Paragraph(null);
		assertEquals(0, para.getSize());
	}

	@Test
	final void testFor1sentence() {
		String sentence = "one.";
		Paragraph para = new Paragraph(sentence);
		String expected = "one";
		assertEquals(1, para.getSize());
		assertEquals(expected, para.getAt(0));
	}

	@Test
	final void testForMoreThan1sentence() {
		String sentence = "one.two.";
		Paragraph para = new Paragraph(sentence);
		String expected = "one";
		assertEquals(2, para.getSize());
		assertEquals(expected, para.getAt(0));
		expected = "two";
		assertEquals(expected, para.getAt(1));
	}

	@Test
	final void testCommaSemicolon() {
		String sentence = "one;two,zebra.";
		Paragraph para = new Paragraph(sentence);
		String expected = "one;two,zebra";
		assertEquals(1, para.getSize());
		assertEquals(expected, para.getAt(0));
	}

	@Test
	final void testForPara() {
		String sentence = "one.two6.";
		Paragraph para = new Paragraph(sentence);
		assertEquals(sentence, para.getPara());
	}
}
