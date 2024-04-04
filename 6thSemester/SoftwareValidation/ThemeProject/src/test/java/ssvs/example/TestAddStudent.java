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

import static junit.framework.Assert.assertNull;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class TestAddStudent {
    private StudentXMLRepo studentFileRepository;
    private StudentValidator studentValidator;
    private Service service;

    /*@BeforeAll
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

    @AfterAll
    static void removeXML() {
        new File("fisiere/studentiTest.xml").delete();
    }*/

    @Test
    public void testAddStudentDuplicate(){

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("1", "Alen", 933, "arsenal@ucl.com");

        Student stud1 = this.service.addStudent(newStudent);
        assertNull(stud1);

        Student stud2 = this.service.addStudent(newStudent);
        assertEquals(newStudent.getID(), stud2.getID());

        this.service.deleteStudent("1");
    }

    @Test
    public void testAddStudentNonDuplicate(){

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

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

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("1", "Alen", 933, "arsenal@ucl.com");
        this.service.addStudent(newStudent);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next().getID(), newStudent.getID());
        this.service.deleteStudent("1");
    }

    @Test
    public void testAddStudentEmptyName(){

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("1", "", 933, "arsenal@ucl.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentNullName(){

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("1", null, 933, "arsenal@ucl.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentValidGroup() {

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("1", "Alen", 933, "arsenal@ucl.com");

        this.service.addStudent(newStudent);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next().getID(), newStudent.getID());

        this.service.deleteStudent("1");
    }

    @Test
    public void testAddStudentInvalidGroup() {

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("1", "Alen", -933, "arsenal@ucl.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentValidEmail() {

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("1", "Alen", 933, "arsenal@ucl.com");

        this.service.addStudent(newStudent);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next().getID(), newStudent.getID());

        this.service.deleteStudent("1");
    }

    @Test
    public void testAddStudentEmptyEmail() {

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("1", "Alen", 933, "");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentNullEmail() {

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("1", "Alen", 933, null);
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentValidId() {

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("1", "Alen", 933, "arsenal@ucl.com");

        this.service.addStudent(newStudent);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next().getID(), newStudent.getID());

        this.service.deleteStudent("1");
    }

    @Test
    public void testAddStudentEmptyId() {

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("", "Alen", 933, "arsenal@ucl.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentNullId() {

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student(null, "Alen", 933, "arsenal@ucl.com");
        assertThrows(NullPointerException.class, () -> this.service.addStudent(newStudent));
        //assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent));
    }

    @Test
    public void testAddStudentGroup0(){

        this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        this.studentValidator = new StudentValidator();
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);

        Student newStudent = new Student("1", "Alen", 0, "arsenal@ucl.com");

        this.service.addStudent(newStudent);
        java.util.Iterator<Student> students = this.service.getAllStudenti().iterator();
        assertEquals(students.next().getID(), newStudent.getID());

        this.service.deleteStudent("1");
    }
}
