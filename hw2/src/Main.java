import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.time.Duration;
import java.time.Instant;
import java.util.*;
import java.util.stream.Collectors;

public class Main {

	private static String readFile(String fileName) throws FileNotFoundException {
		Scanner scanner = new Scanner(new File(fileName));
		String text = "";
		while (scanner.hasNextLine())
			text += scanner.nextLine();
		return text;
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
		String suffixArrayIndexes = "";
		String[] suffixArray = new String[size];
		for (int i = 0; i < matrix.length; i++) {
			bwtString += matrix[i][size - 1];
			String line = String.valueOf(matrix[i]);
			suffixArray[i] = line.substring(0, line.indexOf("$") + 1);
			suffixArrayIndexes += (size - String.valueOf(matrix[i]).indexOf("$") - 1) + " ";
		}

		// The first line of the ***.fm file is the the suffix array
		Path FMFile = Paths.get(textFileName + ".fm");
		try {
			Files.write(FMFile, Collections.singletonList(suffixArrayIndexes), StandardCharsets.UTF_8);
		} catch (IOException e) {
			e.printStackTrace();
		}

		// write suffix array to ***.fm file from the second line on.
		for(String line: suffixArray){
			try {
				Files.write(FMFile, Collections.singletonList(line), StandardCharsets.UTF_8, StandardOpenOption.APPEND);
			} catch (IOException e) {
				e.printStackTrace();
			}
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

		// write FM index to ***.fm file from the (n + 2)th line on.
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

	private static FMFileContent readFMFile(String fileName) throws FileNotFoundException {
		Scanner scanner = new Scanner(new File(fileName + ".fm"));
		int[] suffixArrayIndexes = Arrays.stream(scanner.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
		String[] suffixArray = new String[suffixArrayIndexes.length];
		int[][] indexMatrix = new int[suffixArrayIndexes.length][4];

		for (int i = 0; i < suffixArray.length; i++) {
			suffixArray[i] = scanner.nextLine();
		}

		for (int[] arr : indexMatrix) {
			System.arraycopy(Arrays.stream(scanner.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray(), 0, arr, 0, 4);
		}
		return new FMFileContent(indexMatrix, suffixArrayIndexes, suffixArray);
	}

	//https://www.geeksforgeeks.org/binary-search-a-string/
	private static int binarySearch(String[] arr, String x)
	{
		int l = 0, r = arr.length - 1;
		while (l <= r) {
			int m = l + (r - l) / 2;

			//https://stackoverflow.com/questions/9543046/implement-binary-search-with-string-prefix
			int res = arr[m].startsWith(x) ? 0 : x.compareTo(arr[m]);

			// Check if x is present at mid
			if (res == 0)
				return m;

			// If x greater, ignore left half
			if (res > 0)
				l = m + 1;

				// If x is smaller, ignore right half
			else
				r = m - 1;
		}

		return -1;
	}

	private static void search(String textFileName, String patternFileName) throws FileNotFoundException {
		String text = readFile(textFileName);
		String pattern = readFile(patternFileName);
		FMFileContent fmFileContent = readFMFile(textFileName);
		String bwtString = readFile(textFileName + ".bwt");
		int[] suffixArrayIndexes = fmFileContent.getSuffixArrayIndexes();
		String[] suffixArray = fmFileContent.getSuffixArray();
		int[][] indexMatrix = fmFileContent.getIndexMatrix();
		List<Integer> listOfMatchingPositions = new ArrayList<>();

		Instant start = Instant.now();

		int oneOccuranceIndex = binarySearch(suffixArray, pattern);
		int i = oneOccuranceIndex - 1;
		while(i >= 0 && suffixArray[i].startsWith(pattern))
			listOfMatchingPositions.add(suffixArrayIndexes[i]);
		i = oneOccuranceIndex + 1;
		while(i >= 0 && suffixArray[i].startsWith(pattern))
			listOfMatchingPositions.add(suffixArrayIndexes[i]);
		listOfMatchingPositions.add(suffixArrayIndexes[oneOccuranceIndex]);

		Instant stop = Instant.now();

		System.out.println("Pattern " + pattern + " found in " + text + " " + listOfMatchingPositions.size() + " times at positions: ");
		i = 0;
		for (; i < listOfMatchingPositions.size(); i++){
			System.out.println("pos " + (i + 1) + ": " + listOfMatchingPositions.get(i));
		}
		System.out.println("Search completed in " + Duration.between(start, stop).getSeconds() + " seconds.");
	}

	public static void main(String[] args) {
		String textFileName;
		String patternFileName;
		String text;
		if (args.length >= 4) {
			textFileName = args[0].equals("--search") ? args[1] : args[3];
			patternFileName = args[0].equals("--pattern") ? args[1] : args[3];
			try {
				search(textFileName, patternFileName);
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		} else if (args.length >= 2) {
			textFileName = args[1];
			try {
				text = readFile(textFileName) + "$";
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
