import os
import time
import threading


class Waiter(threading.Thread):
    """Waiter is a class to execute a task on a configurable condition becoming
    true.
    """

    def __init__(self, predicate, callback, frequency=.5):
        """ Constructor
        :param predicate: The condition to evaluate.
        :param callback: The callback to execute when predicate is true.
        :param frequency: The predicate polling frequency.
        """
        super(Waiter, self).__init__()

        self._predicate = predicate
        self._callback = callback
        self._frequency = frequency

    def run(self):
        """The polling function that evaluates the predicate and executes the
        callback when predicate is true.
        """
        while self._predicate():
            time.sleep(self._frequency)

        self._callback()


# # Uncomment for runnable example.
# def is_parent_alive():
#     try:
#         os.kill(os.getppid(), 0)
#         return True
#     except OSError:
#         return False
#
#
# Waiter(is_parent_alive, lambda: os.kill(os.getpid(), 15)).start()
#
# print("This is the main thread sleeping")
# time.sleep(300)
