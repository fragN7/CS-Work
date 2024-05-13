from tkinter import Button, Tk, Toplevel
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
            print("_new__ Creating new instance")
        return cls._instance

    def __init__(self):
        if self._initialized:
            print("Returning already existing instance")
            return
        print("__init__ Creating new instance")

        self._initialized = True
        self.root = Toplevel()
        self.root.title("Menu")
        self.root.configure(bg="#f5f3d5")

        self.current_note_to_clone = None

        self.note_factory = StickyNoteFactory()
        self.sticky_notes_collection = StickyNoteCollection()

        window_width = 400
        window_height = 200
        self.root.geometry(f"{window_width}x{window_height}")

        self.close_button = Button(self.root, text="Close Menu", bg="#DC143C", command=self.close_menu)
        self.close_button.grid(row=0, column=2, sticky="ne")

        button_text_note = Button(self.root, text="New Square Note", bg="#58f577", width=15, height=2, command=self.create_text_note)
        button_text_note.grid(row=1, column=0, padx=5, pady=5)

        button_image_note = Button(self.root, text="New Image Note", bg="#58f577", width=15, height=2, command=self.create_image_note)
        button_image_note.grid(row=1, column=1, padx=5, pady=5)

        button_show_all_notes = Button(self.root, text="Show all Notes", bg="#f5ed58", width=15, height=2, command=self.show_all_notes)
        button_show_all_notes.grid(row=2, column=0, padx=5, pady=5)

        button_show_notes_1_by_1 = Button(self.root, text="Show Notes 1 by 1", bg="#f5ed58", width=15, height=2, command = self.show_notes_1_by_1)
        button_show_notes_1_by_1.grid(row=2, column=1, padx=5, pady=5)

    def close_menu(self):
        self.root.withdraw()

    def create_text_note(self):
        text_note = self.note_factory.create_sticky_note(self.root, "Title...", "Enter your text here",None, "text")
        self.sticky_notes_collection.add_note(text_note)
        text_note.display()

    def create_image_note(self):
        image_note = self.note_factory.create_sticky_note(self.root, "Title...", "Enter your text here",None ,"image")
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
        iterator_window.configure(bg="#f5f3d5")
        curr_note = None
        window_width = 300
        window_height = 150
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

        # Upon next click, iterate over notes and also set current note to clone
        next_button = Button(iterator_window, text="Next", bg="lightgreen", command=lambda: self.set_current_note_to_clone(show_next_note()), width=20, height=2)
        next_button.grid(row=1, column=0, padx=5, pady=5)

        clone_button = Button(iterator_window, text="Duplicate Note", bg="yellow", width=20, height=2, command=lambda : self.clone_note(self.current_note_to_clone))
        clone_button.grid(row=0, column=0, padx=5, pady=5)

        delete_button = Button(iterator_window, text="DELETE", bg="red", command=lambda : self.delete_note(self.current_note_to_clone))
        delete_button.grid(row=1, column=1, padx=5, pady=5)

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
    root.title("Sticky Notes App")
    root.configure(bg="#f5f3d5")

    menu_button = Button(root, text="Menu", command=open_menu, bg="#f5ed58", width=20, height=5)
    menu_button.pack()

    root.mainloop()

if __name__ == "__main__":
    main()
