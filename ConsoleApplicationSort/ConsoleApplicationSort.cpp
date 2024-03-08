// ConsoleApplicationSort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

void quickSort(std::vector<int> & arr, const int & start, const int & end)
{
    if (start >= end)
    {
        return;
    }

    int arrLeft = start, arrRight = end, mid = arr[end];

    while (arrLeft < arrRight)
    {
		while (arr[arrLeft] <= mid && arrLeft < arrRight)
		{
			arrLeft++;
		}
        while (arr[arrRight] >= mid && arrLeft < arrRight)
        {
            arrRight--;
        }
        std::swap(arr[arrLeft], arr[arrRight]);
    }
	if (arr[arrLeft] >= arr[end])
		std::swap(arr[arrLeft], arr[end]);
	else
		arrLeft++;

    quickSort(arr, start, arrLeft - 1);
    quickSort(arr, arrLeft + 1, end);
}

int binarySearch(std::vector<int>& arr, const int & start, const int & end, const int & findValue)
{
    if (start >= end) {
        return -1;
    }
    int mid = start + ((end - start) >> 1);

    if (findValue == arr[mid])
    {
        return mid;
    }
    else if (findValue > arr[mid])
    {
        return binarySearch(arr, mid + 1, end, findValue);
    }
    else
    {
        return binarySearch(arr, start, end - 1, findValue);
    }

}


std::unique_ptr<char[]> replaceAll(const char* str, const char* find, const char* replace) {
	int findLen = std::strlen(find);
	int replaceLen = std::strlen(replace);

	int resultLen = std::strlen(str); // 初始结果长度与原始字符串相同

	const char* pos = str;
	while ((pos = std::strstr(pos, find)) != nullptr) {
		resultLen = resultLen - findLen + replaceLen; // 更新结果长度
		pos += findLen;
	}

	std::unique_ptr<char[]> result(new char[resultLen + 1]); // 使用智能指针动态分配足够的内存空间
	char* dest = result.get();

	pos = str;
	while ((pos = std::strstr(pos, find)) != nullptr) {
		int chunkLen = pos - str; // 计算需要拷贝的长度
		std::strncpy(dest, str, chunkLen); // 拷贝部分内容
		dest += chunkLen;
		std::strncpy(dest, replace, replaceLen); // 拷贝替换内容
		dest += replaceLen;
		pos += findLen;
		str = pos;
	}
	std::strcpy(dest, str); // 拷贝剩余部分

	return result;
}

void stdStringReplaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

int main1()
{
    //std::vector<int> intVector = { 1, 2, 7, 8, 3, 2, 1 };
    //quickSort(intVector, 0, intVector.size() - 1);
    //for (auto it : intVector)
    //{
    //    std::cout << it;
    //}
    //int num = binarySearch(intVector, 0, intVector.size() - 1, 4);
    //if (num != -1) 
    //{
    //    std::cout << "    下标为" << num << "   值为" << intVector[num] << std::endl;
    //}
    //else
    //{
    //    std::cout << "    下标为" << num << "   值为" << -1 << std::endl;
    //}

	char str[] = "这是一串字符串网易是最厉害的公司,网易很棒";
	const char* find = "网易";
	const char* replace = "WY1111111111";

	std::unique_ptr<char[]> replacedStr = replaceAll(str, find, replace);

	std::cout << replacedStr.get() << std::endl;
	replaceAll(str, find, replace);

    std::string str1 = "这是一串字符串网易是最厉害的公司,网易很棒";
    stdStringReplaceAll(str1, find, replace);

	std::cout << str1 << std::endl;
    
    system("pause");
	return 1;
}

void computeLPSArray(const std::string& pattern, std::vector<int>& lps) {
	int len = 0;
	lps[0] = 0;
	int i = 1;
	while (i < pattern.length()) {
		if (pattern[i] == pattern[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else {
			if (len != 0) {
				len = lps[len - 1];
			}
			else {
				lps[i] = 0;
				i++;
			}
		}
	}
}

std::string replaceSubstringKMP(const std::string& mainString, const std::string& oldSubstring, const std::string& newSubstring) {
	std::string modifiedString = mainString;
	int oldSubstringLen = oldSubstring.length();
	int modifiedStringLen = modifiedString.length();

	std::vector<int> lps(oldSubstringLen, 0);
	computeLPSArray(oldSubstring, lps); // 计算部分匹配表

	int i = 0;
	int j = 0;
	while (i < modifiedStringLen) {
		if (oldSubstring[j] == modifiedString[i]) {
			j++;
			i++;
		}
		if (j == oldSubstringLen) {
			modifiedString.replace(i - j, oldSubstringLen, newSubstring);
			modifiedStringLen = modifiedString.length();
			i = i - j + newSubstring.length();
			j = 0;
		}
		else if (i < modifiedStringLen && oldSubstring[j] != modifiedString[i]) {
			if (j != 0) {
				j = lps[j - 1];
			}
			else {
				i++;
			}
		}
	}
	return modifiedString;
}

double calculateElectricityCost(int electricityUsage) {
	std::vector<std::pair<int, double>> rates = { {100, 1.0}, {200, 1.5}, {INT_MAX, 2.0} }; // 存储不同梯度的费率
	double cost = 0.0;
	int remainingElectricity = electricityUsage;

	for (const auto& rate : rates) {
		int threshold = rate.first;
		double currentRate = rate.second;
		if (remainingElectricity > 0) {
			int consumedElectricity = std::min(threshold, remainingElectricity);
			cost += consumedElectricity * currentRate;
			remainingElectricity -= consumedElectricity;
		}
		else {
			break;
		}
	}
	return cost;
}

int main() {
	std::string originalString = "BBC ABCDAB ABCDABCDABDE!";
	std::string newString = replaceSubstringKMP(originalString, "ABCDABD", "Hi");
	std::cout << newString << std::endl;

	int electricityUsage = 732;
	double totalCost = calculateElectricityCost(electricityUsage);
	std::cout << "Total electricity cost for " << electricityUsage << " units: " << totalCost << " yuan" << std::endl;

	system("pause");
	return 0;
}