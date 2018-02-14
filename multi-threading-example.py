import threading
import time

class myThread (threading.Thread):
    def __init__(self, threadID):
        threading.Thread.__init__(self)
        self.threadID = threadID
    def run(self):
        print ("Starting thread %d" % self.threadID)
        excess = len(temp) % num_thread
        itera = len(temp) // num_thread
        if self.threadID < excess:
            itera += 1
        for i in range(itera):
            print ("thread%d: %s" % (self.threadID, time.ctime(time.time())))
            row = self.threadID + i*num_thread
            change_list(self.threadID, row)
        print ("Exiting  thread %d" % self.threadID)

def change_list(threadID, row):
        temp[row][0] = threadID+1

def main():
    time.sleep(20)
    # Create new threads
    threads = [myThread(i) for i in range(num_thread)]

    # Start new Threads
    for t in threads:
        t.start()

    # Main thread wait for all threads to complete
    for t in threads:
        t.join()
    
    print ("Exiting Main Thread")
    print (temp)

if __name__ == "__main__":
    # initialze file scope variables
    temp = [[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0]]
    print (temp)
    num_thread = 2
    main()