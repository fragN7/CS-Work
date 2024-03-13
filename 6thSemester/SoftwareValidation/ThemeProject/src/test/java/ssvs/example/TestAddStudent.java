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

import static junit.framework.Assert.assertNull;
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
    public void testAddStudentDuplicate(){
        Student newStudent = new Student("1", "Alen", 933, "arsenal@ucl.com");

        Student stud1 = this.service.addStudent(newStudent);
        assertNull(stud1);

        Student stud2 = this.service.addStudent(newStudent);
        assertEquals(newStudent.getID(), stud2.getID());

        this.service.deleteStudent("1");
    }

    @Test
    public void testAddStudentNonDuplicate(){
        Student newStudent1 = new Student("1", "Alen", 933, "arsenal@ucl.com");
        Student newStudent2 = new Student("2", "Alen", 933, "arsenal@ucl.com");


        Student stud1 = this.service.addStudent(newStudent1);
        assertNull(stud1);

        Student stud2 = this.service.addStudent(newStudent2);
        assertNull(stud2);

        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next().getID(), newStudent1.getID());
        assertEquals(students.next().getID(), newStudent2.getID());

        this.service.deleteStudent("1");
        this.service.deleteStudent("2");
    }

    @Test
    public void testAddStudentValidName(){
        Student newStudent = new Student("1", "Alen", 933, "arsenal@ucl.com");
        this.service.addStudent(newStudent);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next().getID(), newStudent.getID());
        this.service.deleteStudent("1");
    }

    @Test
    public void testAddStudentEmptyName(){
        Student newStudent = new Student("1", "", 933, "arsenal@ucl.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentNullName(){
        Student newStudent = new Student("1", null, 933, "arsenal@ucl.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentValidGroup() {
        Student newStudent = new Student("1", "Alen", 933, "arsenal@ucl.com");

        this.service.addStudent(newStudent);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next().getID(), newStudent.getID());

        this.service.deleteStudent("1");
    }

    @Test
    public void testAddStudentInvalidGroup() {
        Student newStudent = new Student("1", "Alen", -933, "arsenal@ucl.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentValidEmail() {
        Student newStudent = new Student("1", "Alen", 933, "arsenal@ucl.com");

        this.service.addStudent(newStudent);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next().getID(), newStudent.getID());

        this.service.deleteStudent("1");
    }

    @Test
    public void testAddStudentEmptyEmail() {
        Student newStudent = new Student("1", "Alen", 933, "");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentNullEmail() {
        Student newStudent = new Student("1", "Alen", 933, null);
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentValidId() {
        Student newStudent = new Student("1", "Alen", 933, "arsenal@ucl.com");

        this.service.addStudent(newStudent);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next().getID(), newStudent.getID());

        this.service.deleteStudent("1");
    }

    @Test
    public void testAddStudentEmptyId() {
        Student newStudent = new Student("", "Alen", 933, "arsenal@ucl.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentNullId() {
        Student newStudent = new Student(null, "Alen", 933, "arsenal@ucl.com");
        assertThrows(NullPointerException.class, () -> this.service.addStudent(newStudent));
        //assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentGroup0(){
        Student newStudent = new Student("1", "Alen", 0, "arsenal@ucl.com");

        this.service.addStudent(newStudent);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next().getID(), newStudent.getID());

        this.service.deleteStudent("1");
    }
}
