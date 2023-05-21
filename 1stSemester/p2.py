def read():
    x=input("Enter your number here: ")
    x=int(x)
    print("Your inverted number is:",palindrome(x))

def palindrome(x):
    n=0
    while x>0:
        n=n*10 + x%10
        x=x//10
    return n

