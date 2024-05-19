from tkinter import Button, Tk, Toplevel, font
from StickyNote import StickyNoteFactory
from Iterator import StickyNoteCollection, StickyNoteIterator

# Singleton Pattern - Menu
# Factory Pattern - StickyNoteFactory
# Iterator Pattern - StickyNoteCollection + StickyNoteIterator
# Prototype Pattern - StickyNote clone method
# Template Pattern - Stickynote Abstract class implemented by 2 other classes--> TextStickyNote / ImageStickyNote
class Menu:
    _instance = None

    def __new__(cls, *args, **kwargs):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance._initialized = False
        return cls._instance

    def __init__(self):
        if self._initialized:
            return

        self._initialized = True
        self.root = Toplevel()
        self.root.title("Menu")
        self.root.configure(bg="black")

        self.current_note_to_clone = None

        self.note_factory = StickyNoteFactory()
        self.sticky_notes_collection = StickyNoteCollection()

        window_width = 400
        window_height = 600
        self.root.geometry(f"{window_width}x{window_height}")

        custom_font = font.Font(size=14, weight="bold", font="Helvetica")

        self.close_button = Button(self.root, text="Close", bg="red", font=custom_font, command=self.close_menu)
        self.close_button.place(x=160, y=500, width=90, height=50)

        button_text_note = Button(self.root, text="New Task", bg="white", font=custom_font, command=self.create_text_note)
        button_text_note.place(x=100, y=30, width=200, height=100)

        button_image_note = Button(self.root, text="New Image Task", bg="white", font=custom_font, command=self.create_image_note)
        button_image_note.place(x=100, y=140, width=200, height=100)

        button_show_all_notes = Button(self.root, text="Show all Notes", bg="white", font=custom_font, command=self.show_all_notes)
        button_show_all_notes.place(x=100, y=250, width=200, height=100)

        button_show_notes_1_by_1 = Button(self.root, text="Show 1 by 1", bg="white", font=custom_font, command=self.show_notes_1_by_1)
        button_show_notes_1_by_1.place(x=100, y=360, width=200, height=100)

    def close_menu(self):
        self.root.withdraw()

    def create_text_note(self):
        text_note = self.note_factory.create_sticky_note(self.root, "Title...", "Add your task description here...", None, "text")
        self.sticky_notes_collection.add_note(text_note)
        text_note.display()

    def create_image_note(self):
        image_note = self.note_factory.create_sticky_note(self.root, "Title...", "Add your task description here...", None, "image")
        self.sticky_notes_collection.add_note(image_note)
        image_note.display()

    def show_all_notes(self):
        for note in self.sticky_notes_collection:
            note.window.deiconify()

    def set_current_note_to_clone(self, note):
        self.current_note_to_clone = note

    def show_notes_1_by_1(self):
        iterator = iter(self.sticky_notes_collection)
        iterator_window = Toplevel()
        iterator_window.title("Showcase notes")
        iterator_window.configure(bg="black")
        window_width = 400
        window_height = 300
        iterator_window.geometry(f"{window_width}x{window_height}")

        def show_next_note():
            try:
                current_note = iterator.current()
                note = next(iterator)
                if current_note:
                    current_note.window.withdraw()
                note.window.deiconify()
                return note
            except StopIteration:
                iterator_window.destroy()

        next_button = Button(iterator_window, text="Next", bg="white", font="Helvetica", command=lambda: self.set_current_note_to_clone(show_next_note()), width=20, height=2)
        next_button.place(x=100, y=50, width=150, height=50)

        clone_button = Button(iterator_window, text="Duplicate Note", bg="white", font="Helvetica", command=lambda: self.clone_note(self.current_note_to_clone))
        clone_button.place(x=100, y=120, width=150, height=50)

        delete_button = Button(iterator_window, text="Delete", bg="red", font="Helvetica", command=lambda: self.delete_note(self.current_note_to_clone))
        delete_button.place(x=100, y=190, width=150, height=50)

    def clone_note(self, note):
        note_copy = note.clone()
        self.sticky_notes_collection.add_note(note_copy)

    def delete_note(self, note):
        note.window.withdraw()
        self.sticky_notes_collection.delete_note(note)

def open_menu():
    menu = Menu()
    menu.root.deiconify()

def main():
    root = Tk()
    root.title("Trello 2")
    root.configure(bg="black")
    root.geometry("800x600")

    custom_font = font.Font(size=20, weight="bold")

    menu_button = Button(root, text="Menu", command=open_menu, bg="white", font=custom_font, width=20, height=5)
    menu_button.pack(pady=200)

    root.mainloop()

if __name__ == "__main__":
    main()
