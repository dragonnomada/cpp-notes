#include <iostream>
#include <iomanip>
#include <cstring>
#include <mariadb/conncpp.hpp>

void insertFruta(sql::Connection *conn)
{
    std::string name;
    double price;

    std::cout << "Nombre: ";
    std::cin >> name;
    std::cout << "Precio: ";
    std::cin >> price;

    try {
        // Create a new PreparedStatement
        sql::PreparedStatement *stmnt(conn->prepareStatement("insert into frutas (nombre, precio) values (?, ?)"));
        // Bind values to SQL statement
        stmnt->setString(1, name);
        stmnt->setDouble(2, price);
        // Execute query
        stmnt->executeQuery();
    }
    catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: " << e.what() << std::endl;
   }
}

void showFrutas(sql::Connection *conn)
{
    sql::Statement *stmnt(conn->createStatement());
    // Execute query
    sql::ResultSet *res = stmnt->executeQuery("select * from frutas");
    // Loop through and print results
    int count = 0;
    while (res->next()) {
        std::cout << "| [" << res->getInt(1) << "] ";
        std::cout.width(20);
        std::cout << std::left; 
        std::cout << res->getString(2);
        std::cout << "$ ";
        std::cout.width(7);
        std::cout << std::right; 
        std::cout << std::fixed << std::setprecision(2);
        std::cout << res->getDouble(3);
        std::cout << " x kilo |" << std::endl;
        count++;
    }
    std::cout << "Se encontraron " << count << " frutas en la tienda" << std::endl;
}

void menu(sql::Connection *conn)
{
    while (true)
    {
        std::cout << "\033c";
        std::cout << "Selecciona una opción:" << std::endl;
        std::cout << "1. Ver Frutas" << std::endl;
        std::cout << "2. Agregar Fruta" << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "0. SALIR" << std::endl;

        int option;

        std::cout << ":> ";
        std::cin >> option;

        if (option == 0)
        {
            std::cout << "Cerrando la tienda" << std::endl;
            break;
        }
        else if (option == 1)
        {
            showFrutas(conn);
        }
        else if (option == 2)
        {
            insertFruta(conn);
        }

        std::cout << std::endl << "[Pulsa una tecla para continuar...]" << std::endl;
        std::cin.get();
        std::cin.get();
    }
}

int main()
{
    try
    {
        // Instantiate Driver
        sql::Driver *driver = sql::mariadb::get_driver_instance();

        // Configure Connection
        sql::SQLString url("jdbc:mariadb://localhost:3306/tienda");
        sql::Properties properties({{"user", "admin"}, {"password", "password"}});

        // Establish Connection
        sql::Connection *conn(driver->connect(url, properties));

        std::cout << "Conexión establecida" << std::endl;

        // TODO: TODAS LAS OPERACIONES
        menu(conn);

        conn->close();

        std::cout << "Conexión finalizada" << std::endl;
    }
    catch (sql::SQLException &e)
    {
        std::cout << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
        // Exit (Failed)
        return 1;
    }
}