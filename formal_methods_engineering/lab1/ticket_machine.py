
class TicketMachine:
    def __init__(self):
        self.money = 0

    def execute_command(self, command):
        if command == 'Return':
            if self.money == 0:
                return "Nothing"
            else:
                to_return = self.money
                self.money = 0
                return str(to_return)
        elif int(command) == 5 or int(command) == 10:
            self.money += int(command)
            if self.money >= 20:
                self.money -= 20
                return "Ticket"
            else:
                return "Nothing"



