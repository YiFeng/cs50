print(f"jar.py: {__name__}")

class Jar:
    def __init__(self, capacity=12):
        self._capacity = 0
        self.capacity = capacity
        self._size = 0


    def __str__(self):
        return "🍪" * self.size

    def deposit(self, n):
        if self.size + n > self.capacity:
            raise ValueError("Exceed capacity")
        self._size += n

    def withdraw(self, n):
        if n > self.size:
            raise ValueError("Over withdraw")
        self._size -= n

    @property
    def capacity(self):
        return self._capacity

    @capacity.setter
    def capacity(self, capacity):
        if capacity < 0:
            raise ValueError(f"Invalid capacity {capacity}")
        self._capacity = capacity


    @property
    def size(self):
        return self._size

def main():
    jar = Jar(15)
    print(str(jar.capacity))
    print(str(jar))
    jar.deposit(4)
    print(str(jar))
    jar.withdraw(5)
    print(str(jar))

if __name__ == "__main__":
    main()