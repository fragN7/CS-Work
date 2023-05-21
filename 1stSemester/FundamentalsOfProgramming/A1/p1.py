def read():
    x=input("Enter your number here: ")
    x=int(x)
    print("Your maxed out number is:",max_number(x))

def max_number(a):
    vec=[0,0,0,0,0,0,0,0,0,0]
    a=int(a)
    while a>0:
        vec[a%10]=vec[a%10]+1
        a=a//10
    i=9
    i=int(i)
    n=0
    n=int(n)
    while i>=0:
        while vec[i]>0:
            n=n*10+i
            vec[i]=vec[i]-1
        i=i-1
    return n

