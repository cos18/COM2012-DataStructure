class Hang:
    def __init__(self, coef, exp):
        self.coef = coef
        self.exp = exp
        self.next = None

    def addHang(self, coef, exp):
        if self.next == None:
            self.next = Hang(coef, exp)
        else:
            self.next.addHang(coef, exp)

    def printHang(self):
        if self.coef > 0:
            print("+", end="")
        print("{}x^{}".format(self.coef, self.exp), end="")
        if self.next != None:
            self.next.printHang()
        else:
            print()

def sumPol(f, g):
    if(f.exp > g.exp):
        result = Hang(f.coef, f.exp)
        f = f.next
    elif(f.exp < g.exp):
        result = Hang(g.coef, g.exp)
        g = g.next
    else:
        result = Hang(f.coef + g.coef, f.exp)
        f = f.next
        g = g.next
    while f!=None and g!=None:
        if (f.exp > g.exp):
            result.addHang(f.coef, f.exp)
            f = f.next
        elif (f.exp < g.exp):
            result.addHang(g.coef, g.exp)
            g = g.next
        else:
            result.addHang(f.coef + g.coef, f.exp)
            f = f.next
            g = g.next
    while f!=None:
        result.addHang(f.coef, f.exp)
        f = f.next
    while g != None:
        result.addHang(g.coef, g.exp)
        g = g.next
    return result

def chaPol(f, g):
    if (f.exp > g.exp):
        result = Hang(f.coef, f.exp)
        f = f.next
    elif (f.exp < g.exp):
        result = Hang((-1) * g.coef, g.exp)
        g = g.next
    else:
        result = Hang(f.coef - g.coef, f.exp)
        f = f.next
        g = g.next
    while f != None and g != None:
        if (f.exp > g.exp):
            result.addHang(f.coef, f.exp)
            f = f.next
        elif (f.exp < g.exp):
            result.addHang((-1)*g.coef, g.exp)
            g = g.next
        else:
            result.addHang(f.coef - g.coef, f.exp)
            f = f.next
            g = g.next
    while f != None:
        result.addHang(f.coef, f.exp)
        f = f.next
    while g != None:
        result.addHang((-1)*g.coef, g.exp)
        g = g.next
    return result

fx = Hang(5, 12)
fx.addHang(-3, 9)
fx.addHang(2, 7)
fx.addHang(-10, 5)
fx.addHang(5, 4)
fx.addHang(-8, 3)
fx.addHang(6, 2)
fx.addHang(-4, 1)
fx.addHang(10, 0)

print("f(x) = ", end="")
fx.printHang()

gx = Hang(13, 11)
gx.addHang(7, 10)
gx.addHang(5, 9)
gx.addHang(3, 8)
gx.addHang(-4, 7)
gx.addHang(1, 6)
gx.addHang(-12, 5)
gx.addHang(9, 4)
gx.addHang(-5, 3)
gx.addHang(1, 2)
gx.addHang(7, 1)
gx.addHang(-23, 0)

print("g(x) = ", end="")
gx.printHang()

print("f(x) + g(x) = ", end="")
sumPol(fx, gx).printHang()

print("f(x) - g(x) = ", end="")
chaPol(fx, gx).printHang()

input()