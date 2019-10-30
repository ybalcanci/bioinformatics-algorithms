public class FMFileContent {
	private int[][] indexMatrix;
	private int[] suffixArrayIndexes;
	private String[] suffixArray;

	public FMFileContent(int[][] indexMatrix, int[] suffixArrayIndexes, String[] suffixArray) {
		this.indexMatrix = indexMatrix;
		this.suffixArrayIndexes = suffixArrayIndexes;
		this.suffixArray = suffixArray;
	}

	public int[][] getIndexMatrix() {
		return indexMatrix;
	}

	public int[] getSuffixArrayIndexes() {
		return suffixArrayIndexes;
	}

	public String[] getSuffixArray() {
		return suffixArray;
	}
}
