from __future__ import annotations
from collections.abc import Iterable, Iterator


class StickyNoteIterator(Iterator):
    def __init__(self, notes):
        self._notes = notes
        self._position = 0

    def __next__(self):
        try:
            note = self._notes[self._position]
            self._position += 1
        except IndexError:
            raise StopIteration()
        return note

    def current(self):
        if self._position == 0 or self._position > len(self._notes):
            return None
        return self._notes[self._position - 1]


class StickyNoteCollection(Iterable):
    def __init__(self):
        self._notes = []

    def __iter__(self) -> StickyNoteIterator:
        return StickyNoteIterator(self._notes)

    def add_note(self, note):
        self._notes.append(note)

    def delete_note(self, note):
        self._notes.remove(note)

