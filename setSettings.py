import Tkinter as tk
root = tk.Tk()

root.withdraw();
#root.title("Enter some data");

projectedWidth = raw_input("Enter the width:");
projectedHeight = raw_input("Enter the height:");
velocity = raw_input("Enter the propagation velocity:");

f_settings = open('settings.in','w');
f_settings.write(projectedWidth + "\n" + projectedHeight + "\n" + velocity + "\n" + str(root.winfo_screenwidth()) + "\n" + str(root.winfo_screenheight()) + "\n");  

