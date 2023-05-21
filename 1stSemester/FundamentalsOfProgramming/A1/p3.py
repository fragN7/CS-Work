def read():
    x=int(input("Enter the position you want: "))
    print("The",x,"-th element of the sequence is: ",position(x))

def position(pos):
    p=int(1)
    i=int(2)
    if pos==1:
        return p
    else:
        while p<pos:
            d=int(2)
            t=i
            while t>1:
                if t%d==0:
                   p=p+1
                while t%d==0:
                   t=t//d
                if p!=pos:
                    d=d+1
                else:
                    return d
            i=i+1

