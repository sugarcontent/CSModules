import java.util.Scanner;
import java.io.File;
import java.io.PrintWriter;
import java.lang.Exception;


public class Assign1 {
	
	public static final int ARR_SIZE = 25;
	public static double [][] imageArray = new double[ARR_SIZE][ARR_SIZE];
	public static double [] rowSums = new double[ARR_SIZE];
	public static double [] colSums = new double[ARR_SIZE];
	
	public static void main(String[] args) throws Exception{
		
		int centerX = 0;
		int centerY = 0;
		
		Scanner inFile = new Scanner(new File ("A0124503W.dat"));
		
		for (int i = 0; i < ARR_SIZE; i++) {
			for (int j = 0; j < ARR_SIZE; j++) 
				imageArray[i][j] = inFile.nextDouble();		
		}
		
		preProcess();
		
		centerX = findCenterX();
		centerY = findCenterY();
		
		PrintWriter writer = new PrintWriter("A0124503W_out.dat", "UTF-8");
		writer.println(centerX + " " + centerY + " " + imageArray[centerX][centerY]);
		writer.close();
		
		inFile.close();
	}
	
	public static void preProcess() {
		
		double sumRow = 0.0;
		double sumCol = 0.0;
		
		for (int row = 0; row < ARR_SIZE; row++) {
			for (int col = 0; col < ARR_SIZE; col++) 
				sumRow += imageArray[row][col];
			
			rowSums[row] = sumRow;
			sumRow = 0;
		}
		
		for (int col = 0; col < ARR_SIZE; col++) {
			for (int row = 0; row < ARR_SIZE; row++) 
				sumCol += imageArray[row][col];
			
			colSums[col] = sumCol;
			sumCol = 0;
		}
	}
	
	public static int findCenterX() {
		
		double rowAboveSum = 0.0;
		double rowBelowSum = 0.0;
		double difference = 0.0;
		double lowestDiff = Integer.MAX_VALUE;
		int xValue = 0;
		
		for (int ignoredRow = 0; ignoredRow < ARR_SIZE; ignoredRow++) {
			for (int row = 0; row < ARR_SIZE; row++) {
				
				if (row < ignoredRow) 
					rowAboveSum += rowSums[row];
				else if (row > ignoredRow) 
					rowBelowSum += rowSums[row];		
			}
			
			difference = Math.abs(rowAboveSum - rowBelowSum);
			
			if (difference <= lowestDiff) {
				lowestDiff = difference;
				xValue = ignoredRow;
			}
			
			rowAboveSum = 0.0;
			rowBelowSum = 0.0;
		}
		
		return xValue;
	}
	
	public static int findCenterY() {
		
		double leftColSum = 0.0;
		double rightColSum = 0.0;
		double difference = 0.0;
		double lowestDiff = Integer.MAX_VALUE;
		int yValue = 0;
		
		for (int ignoredCol = 0; ignoredCol < ARR_SIZE; ignoredCol++) {
			for (int col = 0; col < ARR_SIZE; col++) {
				
				if (col < ignoredCol) 
					leftColSum += colSums[col];
				else if (col > ignoredCol) 
					rightColSum += colSums[col];		
			}
			
			difference = Math.abs(leftColSum - rightColSum);
			
			if (difference <= lowestDiff) {
				lowestDiff = difference;
				yValue = ignoredCol;
			}
			
			leftColSum = 0.0;
			rightColSum = 0.0;
		}
		
		return yValue;
	}
}

