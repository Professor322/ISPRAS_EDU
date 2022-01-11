import org.junit.jupiter.api.*;

import static org.junit.jupiter.api.Assertions.assertEquals;

class PhoneLineTest {
    PhoneLine phone_line;

    @BeforeEach
    void setUp() {
        phone_line = new PhoneLine();
    }

    @AfterEach
    void tearDown() {
        phone_line = null;
    }

    //1/0 2/2 3/3 2/3
    //offHook/soundDialTone validNumber/findConnection invalidNumber/continues validNumber/continues
    @Test
    public void TestCase1() {
        assertEquals(phone_line.offHook(), "soundDialTone");
        try { Thread.sleep(100); } catch (Exception ex) {};
        assertEquals(phone_line.validNumber(), "findConnection");
        try { Thread.sleep(100); } catch (Exception ex) {};
        assertEquals(phone_line.invalidNumber(), "continues");
        try { Thread.sleep(100); } catch (Exception ex) {};
        assertEquals(phone_line.validNumber(), "continues");
    }
}