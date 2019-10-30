import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.*;
import java.util.stream.Collectors;

public class Main {

	private static String readFile(String fileName) throws FileNotFoundException {
		Scanner scanner = new Scanner(new File(fileName));
		String text = "";
		while (scanner.hasNextLine())
			text += scanner.nextLine();
		return text + "$";
	}

	private static void burrows_wheeler_transform(String text, String textFileName) {
		int size = text.length();
		char[][] matrix = new char[size][size];

		// Construct matrix
		matrix[0] = text.toCharArray();
		for (int i = 1; i < size; i++) {
			System.arraycopy(matrix[i - 1], 1, matrix[i], 0, size - 1);
			matrix[i][size - 1] = matrix[i - 1][0];
		}

		// Sort matrix
		java.util.Arrays.sort(matrix, Comparator.comparing(String::valueOf));

		// Generate BWT string and suffix array
		String bwtString = "";
		String suffixArray = "";
		for (char[] chars : matrix) {
			bwtString += chars[size - 1];
			suffixArray += (size - String.valueOf(chars).indexOf("$") - 1) + " ";
		}

		// The first line of the ***.fm file is the the suffix array
		Path FMFile = Paths.get(textFileName + ".fm");
		try {
			Files.write(FMFile, Collections.singletonList(suffixArray), StandardCharsets.UTF_8);
		} catch (IOException e) {
			e.printStackTrace();
		}

		// The first line of the ***.bwt file is the the BWT string
		Path BWTFile = Paths.get(textFileName + ".bwt");
		try {
			Files.write(BWTFile, Collections.singletonList(bwtString), StandardCharsets.UTF_8);
		} catch (IOException e) {
			e.printStackTrace();
		}

		generateFMIndex(bwtString, textFileName);
	}

	private static void generateFMIndex(String bwtString, String textFileName) {
		// A -> 0 | C -> 1 | G -> 2 | T -> 3
		int[][] index = new int[bwtString.length()][4];
		switch (bwtString.charAt(0)){
			case 'A': index[0][0]++; break;
			case 'C': index[0][1]++; break;
			case 'G': index[0][2]++; break;
			case 'T': index[0][3]++;
		}
		for(int i = 1; i < bwtString.length(); i++){
			System.arraycopy(index[i - 1], 0, index[i], 0, 4);
			switch (bwtString.charAt(i)){
				case 'A': index[i][0]++; continue;
				case 'C': index[i][1]++; continue;
				case 'G': index[i][2]++; continue;
				case 'T': index[i][3]++;
			}
		}

		// write FM index to ***.fm file from the second line on.
		Path FMFile = Paths.get(textFileName + ".fm");
		for(int[] arr: index){
			try {
				Files.write(FMFile, Collections.singletonList(Arrays.stream(arr)
						.mapToObj(String::valueOf)
						.collect(Collectors.joining(" "))), StandardCharsets.UTF_8, StandardOpenOption.APPEND);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public static void main(String[] args) {
		String textFileName;
		String patternFileName;
		String text;
		String pattern;
		if (args.length >= 4) {
			textFileName = args[0].equals("--search") ? args[1] : args[3];
			patternFileName = args[0].equals("--pattern") ? args[1] : args[3];

			try {
				text = readFile(textFileName);
				pattern = readFile(patternFileName);
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		} else if (args.length >= 2) {
			textFileName = args[1];
			try {
				text = readFile(textFileName);
			} catch (FileNotFoundException e) {
				e.printStackTrace();
				return;
			}
			burrows_wheeler_transform(text, textFileName);
		} else {
			System.out.println("Insufficient number of arguments provided.");
		}
	}
}
