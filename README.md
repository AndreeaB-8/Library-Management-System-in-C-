# Library Project
This C++ project manages a product menu consisting of books and CDs, as well as customer interactions, including purchasing products, managing stock, and calculating the total amount spent by each customer.

## Main Features
- **Product management**: Add products such as books and CDs, each with a specific price, stock quantity, and VAT rate.
- **Customer management**: Add customers, process product purchases, and calculate the total amount spent by each customer.
- **Inventory template class**: A generic class that manages the books purchased by each customer.
- **Menu system**: Allows the user to manage customer interactions via the console interface.

## Project Structure
### Main Classes:
1. **Product**
   - Abstract base class for products.
2. **Book**
   - Derived from `Product`.
3. **CD**
   - Derived from `Product`.
4. **Customer**
   - Base class for customers.
5. **Menu**
   - Centralizes user interactions.
   - Allows adding and viewing products, and making purchases.

### Functionality
- Add products (books and CDs)
- Add customers
- Assign products to customers (purchases)
- View the total amount spent by each customer
- Check remaining stock for each product
- Search for products by title
- Sort the library’s books by price
