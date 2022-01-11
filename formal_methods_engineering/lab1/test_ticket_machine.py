from unittest import TestCase
import ticket_machine as tm


class TicketMachineTest(TestCase):
    def test_ticket_machine(self):
        input_alphabet = ["Return", "5", "10"]
        output_alphabet = ["Ticket", "Nothing", "5", "10", "15"]
        test_file = open("ticket_machine.test", "r")

        for sequence in test_file:
            ticket_machine = tm.TicketMachine()
            for step in sequence.strip().split(' '):
                i_o = step.split('/')
                res = ticket_machine.execute_command(input_alphabet[int(i_o[0])])
                golden = output_alphabet[int(i_o[1])]
                self.assertEqual(res, golden, "FAIL: {} != {}".format(res, golden))
