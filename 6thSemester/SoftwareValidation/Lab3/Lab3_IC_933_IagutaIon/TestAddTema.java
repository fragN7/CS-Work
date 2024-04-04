package ssvv.example;

import domain.Tema;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import repository.TemaXMLRepo;
import service.Service;
import validation.TemaValidator;
import validation.ValidationException;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class TestAddTema {

    private TemaXMLRepo temaFileRepository;
    private TemaValidator temaValidator;
    private Service service;

    /*@BeforeAll
    static void createXML() {
        File xml = new File("fisiere/temeTest.xml");
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
    public void setup() {
        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);
    }

    @AfterAll
    static void removeXML() {
        new File("fisiere/temeTest.xml").delete();
    }*/

    @Test
    void testAddAssignmentValidAssignment() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema("1", "SVSS", 1, 1);
        this.service.addTema(newTema);
        assertEquals(this.service.getAllTeme().iterator().next(), newTema);
    }

    @Test
    void testAddAssignmentEmptyID() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema("", "SVSS", 1, 1);
        assertThrows(ValidationException.class, () -> this.service.addTema(newTema));
    }

    @Test
    void testAddAssignmentNullID() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema(null, "SVSS", 1, 1);
        assertThrows(NullPointerException.class, () -> this.service.addTema(newTema));
    }
}
