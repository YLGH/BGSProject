import boardControlLib as b
import time

test = b.BoardControlLib()

test.initialize_card()

time.sleep(2)

test.start_logging()

time.sleep(5)

test.stop_logging()