"""

Reverse and add integer problem. Given integer input, check first and last digits.
If they are not equal, take reverse of integer and add together e.g. 123 + 321.
Repeat until you come to a number in which the first and last digits are equal. 
Output the final integer, and the amount of additions needed to get the result.

Examples:

Input: 123
Output: 444 1

Input: 945
Output: 11781 3



"""

def reverse(num):
    return int(str(num)[::-1])


def checkFirstLast(num):
    return(str(num)[0] == str(num)[-1])


def reverseAdd(num):
    global count
    if checkFirstLast(num):
        print(num, " ", count)
    else:
        print(num, " + ", reverse(num), " = ", num + reverse(num) )
        num += reverse(num)
        count += 1
        print(count)
        reverseAdd(num)

count = 0
a = int(input("Enter number: "))

reverseAdd(a)