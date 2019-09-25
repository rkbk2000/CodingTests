package wiki;

import java.util.ArrayList;

public class Paragraph {

	private ArrayList<String> sentences_;
	private String para_ = null;

	public final static String PARA_DELIMITER = "\\.";

	public Paragraph(String para) {
		para_ = para;
		sentences_ = StringScanner.scanString(para, PARA_DELIMITER);
	}

	public String getAt(int index) {
		return sentences_.get(index);
	}

	public int getSize() {
		return sentences_.size();
	}

	public ArrayList<String> getElements() {
		return sentences_;
	}

	public String getPara() {
		return para_;
	}

}
