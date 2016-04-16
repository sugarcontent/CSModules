import java.util.Scanner;

public class Main {
	
	public static int numVillages, numOffices;
	public static int[] value;
	public static int[][] distance, bestValue;
	
	public static void main(String[] args){
		
		Scanner sc = new Scanner(System.in);
		
		numVillages = sc.nextInt();
		numOffices = sc.nextInt();
		
		distance = new int[numVillages][numVillages];
		bestValue = new int[numVillages][numOffices];
		
		value = new int[numVillages];
		
		for(int i=0; i<numVillages; i++)
			value[i] = sc.nextInt();	
		
		System.out.println(findMin(numVillages-1, numOffices-1));
		sc.close();
		
	}
	
	public static int findDist(int x, int y) {
		
		if(distance[x][y] == 0) {
			
			int middle = x + (y - x)/2;
			
			for(int i=x; i<=y; i++)
				distance[x][y] += Math.abs(value[i] - value[middle]);
		}
		
		return distance[x][y];
	}
	
	public static int findMin(int end, int office) {
		
		if(office == 0) {
			findDist(0, end);
			return distance[0][end];
		}
		
		if(bestValue[end][office] != 0)
			return bestValue[end][office];
		
		int min = Integer.MAX_VALUE;
		
		for(int i=end-1; i >= office - 1; i--) {
			min = Math.min(findMin(i, office - 1) + findDist(i+1, end), min);
		}
		
		return bestValue[end][office] = min;
	}
}
