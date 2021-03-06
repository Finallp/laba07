// Copyright 2021 Your Name <your_email>

// cd c++_lab07/lab-07-http-server/cmake-build-debug/
// sudo ./demo 127.0.0.1 80
// curl  -H 'Content-Type: application/json' --data '{"input":"hel"}' http://localhost/v1/api/suggest

#include <http_server.hpp>

namespace po = boost::program_options;  // from <boost/program_options.hpp>

int main(int argc, char *argv[]) {

  std::shared_ptr<std::timed_mutex> mutex =
            std::make_shared<std::timed_mutex>();
    std::shared_ptr<JsonStorage> storage =
            std::make_shared<JsonStorage>("../suggestions.json");
    std::shared_ptr<CallSuggestions> suggestions =
            std::make_shared<CallSuggestions>();

  // Проверяем аргументы командной строки.
  try {
    if (argc != 3) {
      std::cerr << "Usage: suggestion_server <address> <port> \n"
                << "Example:\n"
                << "     127.0.0.1 80\n";
      return EXIT_FAILURE;
    }
    //IP
    auto const address = net::ip::make_address(argv[1]);
    //Порт
    auto const port = static_cast<uint16_t>(std::atoi(argv[2]));

    // контекст ввода-вывода
    net::io_context ioc{1};
    // Передаём адрес и порт сервера
    tcp::acceptor acceptor {ioc, {address, port}};
    //В потоке обновляем коллекцию и формируем предложения для пользователя
    std::thread{suggestion_updater, storage, suggestions, mutex}.detach();
    for (;;) {
      //новое соединение
      tcp::socket socket{ioc};
      // Блокируем, пока не получим соединение
      acceptor.accept(socket);
      // Запускаем сессию, передавая владение сокетом
      std::thread{std::bind(
                      &do_session,
                      std::move(socket),
                      suggestions,
                      mutex)}.detach();
    }
  } catch (std::exception& e) {

    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
