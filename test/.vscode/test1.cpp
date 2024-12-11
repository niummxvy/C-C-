#include <iostream>
using namespace std;

int main()
{
	int n;
	while (cin >> n)
	{
		int nums[100];
		int temp, i, j,k;
		for (int in = 0; in < n; in++)//input
		{
			cin >> nums[in];
		}
		for (i = 1; i < n; i++)
		{
			
			for (j = 0; j < n - i; j++)
			{
				if (nums[j] > nums[j + 1])
				{
					temp = nums[j];
					nums[j] = nums[j + 1];
					nums[j + 1] = temp;
				}
			}
		}
		for (k = 0; k < n; k++)
			cout << nums[k] << " ";
		cout << endl;
	}

	return 0;
}