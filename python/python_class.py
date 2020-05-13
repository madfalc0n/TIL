class FourCal:
        def __init__(self, first, second):
            self.first = first
            self.second = second
        def setdata(self, first, second):
            self.first = first
            self.second = second
        def add(self):
            return self.first + self.second
        def mul(self):
            return self.first * self.second
        def sub(self):
            return self.first - self.second
        def div(self):
            return self.first / self.second
        
        
a = FourCal(4, 2)
print(a.add(), a.mul(), a.sub(), a.div())