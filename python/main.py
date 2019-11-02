from threading import Thread
from functools import partial
from random import SystemRandom
from time import sleep

should_wait = partial(SystemRandom().getrandbits)


class Int:
    a = 0

    def slow_assignment(self, value):
        if should_wait:
            sleep(1)

        self.a = value


a = Int()
threads = [
    Thread(target=a.slow_assignment, args=[1]),
    Thread(target=a.slow_assignment, args=[2]),
]

for thread in threads:
    thread.start()

for thread in threads:
    thread.join()

print(a.a)
