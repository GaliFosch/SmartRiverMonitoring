import tkinter as tk

window = tk.Tk()
window.geometry("500x200")
window.title("River Monitoring Dashboard")

currOpeningLevel = tk.StringVar()
currState = tk.StringVar()

# This is the command function for the slider, which updates the label with the current value
def sliderLabelUpdate(newvalue):
    sliderLabel.config(text=f"Selected opening level: {newvalue}%")

def update():
    window.after(100, update)

# Setup State label
currStateLabel = tk.Label(master=window, text="Current State: " + currState.get(), justify="left", anchor="w")
currStateLabel.grid(sticky="w", row=0, column=0)

# Setup Current Opening Level label
currOpeningLevelLabel = tk.Label(master=window, text="Current Opening Level: " + currOpeningLevel.get(), justify="left", anchor="w")
currOpeningLevelLabel.grid(sticky="w", row=1, column=0)

# Setup slider for manually controlling the valve opening level and its label
slider = tk.Scale(master=window, from_=0, to=100, tickinterval=10, orient="horizontal", length=400, showvalue=False, command=sliderLabelUpdate)
slider.grid(row=2, column=0)
sliderLabel = tk.Label(master=window, text=f"Selected opening level: " + currOpeningLevel.get(), justify="left", anchor="w")
sliderLabel.grid(sticky="w", row=3, column=0)

window.mainloop()