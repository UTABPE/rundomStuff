#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cmath>

using namespace std;

//-------------------------------------Binary Search----------------------------------------

bool Binary_Search(int arr[], int size, int x)
{
	int left = 0;
	int right = size-1;
	while (left <= right)
	{
		if (arr[(left + right) / 2] == x) return true;
		else if (arr[(left + right) / 2] < x) left = (left + right) / 2 + 1;
		else right = (left + right) / 2 - 1;
	}
	return false;
}

//--------------------------------------Bubble Sort---------------------------------------

void Bubble_Sort(int arr[], int size)
{
	for (int i = 0; i < size; size--)
	{
		bool b = false;
		for (int p = 0; p < size - 1; p++)
		{
			if (arr[p] > arr[p + 1])
			{
				b = true;
				swap(arr[p], arr[p + 1]);
			}
		}
		if (b == false) break;
	}
}

//-------------------------------------Insertion Sort----------------------------------------

void Insertion_Sort(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int j = i;
		while (j > 0 and arr[j] < arr[j - 1])
		{
			swap(arr[j], arr[j - 1]);
			j--;
		}
	}
}

//-------------------------------------Selection Sort----------------------------------------

void Selection_Sort(int arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (arr[i] > arr[j]) swap(arr[i], arr[j]);
		}
	}
}

//--------------------------------------Merge Sort---------------------------------------

void Merge(int arr[], int p[], int p_size, int q[], int q_size)
{
	int i = 0;
	int j = 0;
	int k = 0;

	while (i < p_size and j < q_size)
	{
		if (p[i] <= q[j])
		{
			arr[k] = p[i];
			i++;
		}
		else
		{
			arr[k] = q[j];
			j++;
		}

		k++;
	}

	while (i < p_size)
	{
		arr[k] = p[i];
		i++;
		k++;
	}

	while (j < q_size)
	{
		arr[k] = q[j];
		j++;
		k++;
	}
}

void Merge_Sort(int arr[], int size)
{
	if (size == 1) return;
	int start = 0;
	int end = size - 1;
	int mid = end / 2;
	int p_size = mid + 1;
	int q_size = end - mid;
	int p[p_size];
	int q[q_size];

	for (int i = start; i <= mid; i++) p[i] = arr[i];

	for (int i = mid + 1; i <= end; i++) q[i - mid - 1] = arr[i];

	Merge_Sort(p, p_size);
	Merge_Sort(q, q_size);
	Merge(arr, p, p_size, q, q_size);
}

//---------------------------------------Quick Sort--------------------------------------

int Partition(int arr[], int start, int end)
{
	int pivot = arr[end];
	int partition_index = start;

	for (int i = start; i < end; i++)
	{
		if (arr[i] <= pivot)
		{
			swap(arr[i], arr[partition_index]);
			partition_index++;
		}
	}

	swap(arr[partition_index], arr[end]);

	return partition_index;
}

void Quick_Sort(int arr[], int start, int end)
{
	if (start < end)
	{
		int partition_index = Partition(arr, start, end);
		Quick_Sort(arr, start, partition_index - 1);
		Quick_Sort(arr, partition_index + 1, end);
	}
}

//-------------------------------------Heap Sort----------------------------------------

void Heapify(int arr[], int size, int index)
{
	int left_child_index = 2 * index + 1;
	int right_child_index = 2 * index + 2;

	int max = index;

	if (left_child_index < size and arr[left_child_index] > arr[max]) max = left_child_index;
	if (right_child_index < size and arr[right_child_index] > arr[max]) max = right_child_index;

	if (max != index) 
	{
		swap(arr[max], arr[index]);
		Heapify(arr, size, max);
	}
}

void Heap_Sort(int arr[], int size)
{
	for (int index = size / 2; index >= 0; index--)
	{
		Heapify(arr, size, index);
	}

	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);
		Heapify(arr, i, 0);
	}
}

//--------------------------------------Shell Sort---------------------------------------

void Shell_Sort(int arr[], int size)
{
	int j = 0;

	int gap = size / 2;

	while (gap > 0)
	{
		for (int i = gap; i < size; i++)
		{
			for (int k = i - gap; k >= 0; k -= gap)
			{
				if (arr[k + gap] >= arr[k]) break;
				else swap(arr[k + gap], arr[k]);
			}
		}

		gap /= 2;
	}
}

//-------------------------------------Counting Sort----------------------------------------

void Counting_Sort(int arr[], int size, int max)
{
	int help_array[max + 1];

	for (int i = 0; i <= max; i++) help_array[i] = 0;

	int copy_array[size];
	
	for (int i = 0; i < size; i++) copy_array[i] = arr[i];

	for (int i = 0; i < size; i++) help_array[arr[i]]++;

	for (int i = 1; i <= max; i++) help_array[i] += help_array[i - 1];

	for (int i = size - 1; i >= 0; i--) 
	{
		arr[help_array[copy_array[i]] - 1] = copy_array[i];
		help_array[copy_array[i]]--;
	}
}

//---------------------------------------Radix Sort--------------------------------------

int Get_Max(int arr[], int size)
{
	int max = arr[0];
	for (int i = 1; i < size; i++) if (arr[i] > max) max = arr[i];
	return max;
}

void Counting_Radix_Sort(int arr[], int size, int digit)
{
	int count_array[10];
	for (int i = 0; i < 10; i++) count_array[i] = 0;

	int copy_array[size];
	for (int i = 0; i < size; i++) copy_array[i] = arr[i];

	for (int i = 0; i < size; i++) count_array[(arr[i] / digit) % 10]++;

	for (int i = 1; i < 10; i++) count_array[i] += count_array[i - 1];

	for (int i = size - 1; i >= 0; i--)
	{
		arr[count_array[(copy_array[i] / digit) % 10] - 1] = copy_array[i];
		count_array[(copy_array[i] / digit) % 10]--;
	}
}

void Radix_Sort(int arr[], int size)
{
	int max = Get_Max(arr, size);

	for (int digit = 1; max / digit > 0; digit *= 10) Counting_Radix_Sort(arr, size, digit);
}

//------------------------------------Binary Tree Sort-----------------------------------------

struct Binary_Tree_Node
{
	int data;
	Binary_Tree_Node* left_child;
	Binary_Tree_Node* right_child;
};

void Insert_Node(Binary_Tree_Node* &root, int number)
{
	if (root == NULL)
	{
		root = new Binary_Tree_Node;
		root->data = number;
		root->left_child = NULL;
		root->right_child = NULL;
		return;
	}
	else if (number > root->data) Insert_Node(root->right_child, number);
	else Insert_Node(root->left_child, number);
}

void Recorder(int arr[], vector<int> vec, Binary_Tree_Node* node)
{
	if (node != NULL)
	{
		Recorder(arr, vec, node->left_child);
		//vec.push_back(node->data);
		cout << node->data << " ";
		Recorder(arr, vec, node->right_child);
	}
}

void Binary_Tree_Sort(int arr[], int size)
{
	Binary_Tree_Node* root;
	root = NULL;

	for (int i = 0; i < size; i++) Insert_Node(root, arr[i]);

	vector<int> vec;

	Recorder(arr, vec, root);

}

//------------------------------------Bucket Sort-----------------------------------------

void Bucket_Sort(int arr[], int size)
{
	int min = arr[0];
	int max = arr[0];

	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max) max = arr[i];
		if (arr[i] < min) min = arr[i];
	}

	int bucket_number = max - min + 1;
	vector<int> bucket[bucket_number];

	for (int i = 0; i < bucket_number; i++)
	{
		bucket[i] = vector<int>();
	}

	for (int i = 0; i < size; i++) bucket[arr[i] - min].push_back(arr[i]);

	int index = 0;

	for (int i = 0; i < bucket_number; i++)
	{
		int bucket_size = bucket[i].size();
		
		if (bucket_size > 0)
		{
			for (int j = 0; j < bucket_size; j++)
			{
				arr[index] = bucket[i][j];
				index++;
			}
		}
	}
}

//-------------------------------------Comb Sort----------------------------------------

void Comb_Sort(int arr[], int size)
{
	double shrink_factor = 1.247;
	int gap = size / shrink_factor;

	for (gap; gap > 0; gap /= shrink_factor)
	{
		for (int k = gap; k < size; k++)
		{
			if (arr[k] < arr[k - gap]) swap(arr[k], arr[k - gap]);
		}
	}

	Bubble_Sort(arr, size);
}

//-------------------------------------Intro Sort----------------------------------------

void Intro_Sort(int arr[], int size)
{
	int partition_size = Partition(arr, 0, size - 1);

	if (partition_size < 16) Insertion_Sort(arr, size);
	else if (partition_size > 2 * log(size)) Heap_Sort(arr, size);
	else Quick_Sort(arr, 0, size - 1);
}

//-----------------------------------------------------------------------------

int main()
{
	srand(time(NULL));

	int size = 100;

	int arr[size];

	for (int i = 0; i < size; i++) arr[i] = 100 + rand() % 900;

	//Bubble_Sort(arr, size);
	//Selection_Sort(arr, size);
	//Insertion_Sort(arr, size);
	//Merge_Sort(arr, size);
	//Quick_Sort(arr, 0, size - 1);
	//Heap_Sort(arr, size);
	//Shell_Sort(arr, size);
	//Counting_Sort(arr, size, 1000);
	//Radix_Sort(arr, size);
	//*Binary_Tree_Sort(arr, size);
	//Bucket_Sort(arr, size);
	//Comb_Sort(arr, size);
	//Intro_Sort(arr, size);

	for (int i = 0; i < size; i++) 
	{
		cout << arr[i] << " ";
		if (i % 10 == 9) cout << endl;
	}

	cout << endl << 1 * Binary_Search(arr, size, 100 + rand() % 900) << endl;

	return 0;
}