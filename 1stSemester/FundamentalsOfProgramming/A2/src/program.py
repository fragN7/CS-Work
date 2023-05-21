import math

def menu_complex(): #prints menu (easy)
    print("Complex Numbers App")
    print("Write '1' in order to read a complex number")
    print("Write '2' in order to show all the complex numbers")
    print("Write '3 in order to show the longest sequence of complex numbers which have the same modulus")
    print("Write '4' in order to show the longest sequence of complex numbers which have the difference between the modulus of consecutive numbers a prime number")
    print("Write '5' if you want to exit the program \n")

def add_complex_list(re,im,comDict): #adds real part and imaginary part to the dictionary list (kind of a setter)
    comDict["re"].append(re)
    comDict["im"].append(im)

def get_real(comDict,re):
    return comDict["re"][re]

def get_imag(comDict,im):
    return comDict["im"][im]

def modulus_calc(re,im): #calculates the modulus
    return math.sqrt(re*re+im*im)

def is_prime(x): #prime number checker
    if x<2:
        return False
    if x!=2 and x%2==0:
        return False
    d=int(3)
    while d*d<x:
        if x%d==0:
            return False
        d=d+2
    return True

def display_complex(comDict): #shows all numbers
    for x in range(0, len(comDict["re"])):
        print_complex(get_real(comDict,x),get_imag(comDict,x))

def print_complex(re,im): #print a complex number
    if re:
        if im > 0:
            print(re, "+", im, "i")
        elif im < 0:
            print(re, "-", abs(im), "i")
        else:
            print(re)
    else:
        if im > 0:
            print( im, "i")
        elif im < 0:
            print( "-", abs(im), "i")
        else:
            print(re)

def print_property(i,smax,comDict): #print properties
    for x in range(i-smax,i+1):
        print_complex(get_real(comDict,x),get_imag(comDict,x))

def third_property(comDict): #computes the starting and finishing position for the given property
    s=int(0)
    smax=int(0)
    i=int(0)
    for x in range(0, len(comDict["re"])-1):
        if modulus_calc(get_real(comDict,x),get_imag(comDict,x))==modulus_calc(get_real(comDict,x+1),get_imag(comDict,x+1)):
            s=s+1
        elif s > smax:
            smax = s
            i = x
            s = 0
        else:
            s = 0
    if s>smax:
        smax=s
        i=len(comDict["re"])-1
    if smax:
        print_property(i, smax, comDict)
    else:
        print("We are sorry, but we have no such sequence")

def seventh_property(comDict): #computes the starting and finishing position for the given property
    s = int(0)
    smax = int(0)
    i=int(0)
    for x in range(0, len(comDict["re"]) - 1):
        if is_prime(abs(modulus_calc(get_real(comDict,x), get_imag(comDict,x)) - modulus_calc(get_real(comDict,x+1), get_imag(comDict,x+1)))):
            s = s + 1
        elif s > smax:
            smax = s
            i = x
            s=0
        else:
            s=0
    if s>smax:
        smax=s
        i=len(comDict["re"])-1
    if smax:
        print_property(i, smax, comDict)
    else:
        print("We are sorry, but we have no such sequence")

def read_complex(comDict): #reads real and imaginary part of complex number
    while True:
        try:
            re = int(input("Please write the real part of your complex number :"))
            im = int(input("Please write the imaginary part of your complex number :"))
            print_complex(re,im)
            add_complex_list(re,im,comDict)
            return None
        except ValueError:
            print("Invalid value!")

def test_fun(): #testin boring
    assert is_prime(0)==False
    assert is_prime(-2)==False
    assert is_prime(5)==True
    assert is_prime(3)==True
    assert is_prime(3.0)==True
    assert is_prime(4.2)==False

def start():
    comDict = {'re':[1,2,2,2,0,0,4,3,3,0],'im':[2,1,2,0,5,12,3,4,4,23]}
    menu_complex()
    while True:
        command=input("Please write your option:")
        if command =="1":
            read_complex(comDict)
        elif command =="2":
            display_complex(comDict)
        elif command =="3":
            third_property(comDict)
        elif command == "4":
            seventh_property(comDict)
        elif command == "5":
            return None
        else:
            print("Invalid command!")

start()