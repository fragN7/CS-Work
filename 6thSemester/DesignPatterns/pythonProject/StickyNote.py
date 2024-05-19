import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk


class StickyNoteFactory:
    @staticmethod
    def create_sticky_note(root, title, content, image, note_type):
        if note_type == "text":
            return TextStickyNote(root, title, content)
        elif note_type == "image":
            return ImageStickyNote(root, title, content, image)
        else:
            raise ValueError("Invalid note type")


class StickyNote:
    def __init__(self, root, title, content):
        self.root = root
        self.title = title
        self.content = content


        self.window = tk.Toplevel(self.root)
        self.window.configure(bg="black")
        self.window.title("Note")

        self.save_button = tk.Button(self.window, text="Save", bg="white", command=self.update_sticky_note)
        self.save_button.pack()



    def hide_note(self):
        self.window.withdraw()

    def display(self):
        self.window.mainloop()

    def update_sticky_note(self):
        self.hide_note()

    def clone(self):
       pass

class TextStickyNote(StickyNote):
    def __init__(self, root, title, content):
        super().__init__(root, title, content)

        self.title_entry = tk.Entry(self.window, font=("Helvetica", 12, "bold"),bg="white")
        self.title_entry.insert(0, self.title)
        self.title_entry.pack()

        self.note_entry = tk.Text(self.window, wrap="word", height=10, width=50, bg="white")
        self.note_entry.insert(tk.END, self.content)
        self.note_entry.pack()

    def clone(self):
        return TextStickyNote(self.root, self.title, self.content)

    def update_sticky_note(self):
        self.update_title()
        self.update_content()
        self.hide_note()
        print("Updated sticky note")

    def update_title(self):
        self.title = self.title_entry.get()

    def update_content(self):
        self.content = self.note_entry.get("1.0", tk.END)




class ImageStickyNote(StickyNote):
    def __init__(self, root, title, content, image_path):
        super().__init__(root, title, content)

        self.choose_image_button = tk.Button(self.window, text="Choose Image", command=self.choose_image)
        self.choose_image_button.pack()

        self.image_label = tk.Label(self.window)
        self.image_label.pack()

        if image_path is None:
            self.image_path = None
        else:
            self.image_path = image_path
            self.set_note_image(image_path)

        self.note_entry = tk.Text(self.window, wrap="word", height=10, width=50, bg="white")
        self.note_entry.insert(tk.END, self.content)
        self.note_entry.pack()

    def set_note_image(self, image_path):
        image = Image.open(image_path)
        max_width = 512
        max_height = 512
        image.thumbnail((max_width, max_height))

        photo = ImageTk.PhotoImage(image)
        self.image_label.configure(image=photo)
        self.image_label.image = photo

    def choose_image(self):
        file_path = filedialog.askopenfilename(initialdir="/", title="Select Image File",
                                               filetypes=(("Image Files", "*.png;*.jpg;*.jpeg;*.gif"), ("All Files", "*.*")))
        if file_path:
            self.image_path = file_path
            self.set_note_image(file_path)

    def clone(self):
        return ImageStickyNote(self.root, self.title, self.content,self.image_path)

    def update_sticky_note(self):
        self.update_content()
        self.hide_note()
        print("Updated sticky note")


    def update_content(self):
        self.content = self.note_entry.get("1.0", tk.END)
