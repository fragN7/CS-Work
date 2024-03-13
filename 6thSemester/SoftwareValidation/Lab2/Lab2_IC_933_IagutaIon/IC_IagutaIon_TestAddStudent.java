package ssvs.example;

import domain.Student;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import repository.StudentXMLRepo;
import service.Service;
import validation.StudentValidator;
import validation.ValidationException;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class TestAddStudent {
    private StudentXMLRepo studentFileRepository;
    private StudentValidator studentValidator;
    private Service service;

    @BeforeAll
    static void createXML() {
        File xml = new File("fisiere/studentiTest.xml");
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(xml))) {
            writer.write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n" +
                    "<inbox>\n" +
                    "\n" +
                    "</inbox>");
            writer.flush();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    @BeforeEach
    void setup() {
        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);
    }

    @AfterAll
    static void removeXML() {
        new File("fisiere/studentiTest.xml").delete();
    }

    @Test
    void testAddStudentOnGroup() {
        Student newStudent1 = new Student("100", "a", 933, "wasd");
        Student newStudent2 = new Student("101", "a", -1, "wasd");
        Student newStudent3 = new Student("102", "a", 0, "wasd");
        this.service.addStudent(newStudent1);
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent2));
        this.service.addStudent(newStudent3);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next(), newStudent1);
//        assertEquals(students.next(), newStudent1);
        assertEquals(students.next(), newStudent3);

        this.service.deleteStudent("100");
        this.service.deleteStudent("102");
    }

    @Test
    void testAddStudentOnName() {
        Student newStudent1 = new Student("1111111", "Alen", 933, "wasd");
        Student newStudent2 = new Student("1111112", "", 933, "wasd");
        Student newStudent3 = new Student("1111113", null, 933, "wasd");
        this.service.addStudent(newStudent1);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next(), newStudent1);
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent2));
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent3));
    }
}
