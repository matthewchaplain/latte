#include "journal_logger.h"

int main() {
  JournalLogger<int> logger("int_request");
  logger.LogRequest(42, 76);
}