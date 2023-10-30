/**
 * \file stock.h
 * \brief Data structures and algorithms to manage stock data.
 */

#ifndef __STOCK_H__
#define __STOCK_H__

#include <stdbool.h>

/**
 * \brief Stock data structure.
 */
struct stock_item {
    int id;                   /**< Unique identifier of the stock. */
    int price;                /**< Price of the stock. */
    int available;            /**< Number of stock available. */
    struct stock_item *left;  /**< Pointer to the left child. */
    struct stock_item *right; /**< Pointer to the right child. */
};

/**
 * \brief Create a new stock item.
 *
 * \param id Unique identifier of the stock.
 * \param price Price of the stock.
 * \param available Number of stock available.
 * \return Pointer to the new stock item.
 */
struct stock_item *stock_alloc(int id, int price, int available);

/**
 * \brief Delete a tree of stocks.
 *
 * \param root Root of the tree to delete.
 */
void stock_free(struct stock_item *root);

/**
 * \brief Insert a given stock item to an existing tree of stocks.
 *
 * \param root Root of the tree to insert the stock item.
 * \param item Stock item to insert.
 * \return Pointer to the root of the tree.
 */
struct stock_item *stock_insert(struct stock_item *root, struct stock_item *item);

/**
 * \brief Search for a stock item with a given id.
 *
 * \param root Root of the tree to search.
 * \param id Unique identifier of the stock item to search.
 * \return Pointer to the stock item if found, NULL otherwise.
 */
struct stock_item *stock_find(struct stock_item *root, int id);

/**
 * \brief Buy a given number of stocks.
 *
 * \param root Root of the tree to buy stocks from.
 * \param id Unique identifier of the stock to buy.
 * \param amount Number of stocks to buy.
 * \return True if the purchase is successful, false otherwise.
 */
bool stock_buy(struct stock_item *root, int id, int amount);

/**
 * \brief Sell a given number of stocks.
 *
 * \param root Root of the tree to sell stocks to.
 * \param id Unique identifier of the stock to sell.
 * \param amount Number of stocks to sell.
 * \return True if the sale is successful, false otherwise.
 */
bool stock_sell(struct stock_item *root, int id, int amount);

/**
 * \brief Dump the stock tree information into a string.
 *
 * Note that this function blindly assumes that there is enough space for the
 * dumped string. The caller must ensure that the buffer is large enough.
 *
 * \param root Root of the tree to dump.
 * \param buffer Buffer to store the dumped string.
 */
void stock_dump(struct stock_item *root, char *buf);

/**
 * \brief Print the stock tree in the human-readable format.
 *
 * \param item Stock tree to print.
 */
void stock_print(struct stock_item *root);

/**
 * \brief Initialize the stock tree from a status file.
 *
 * The status file is a regular text file with each line representing a stock
 * item information. Each element of the line is separated by a single space:
 * \verbatim
 * <id> <price> <amount of stock available>
 * \endverbatim
 *
 * \param filename Name of the status file.
 * \return Pointer to the root of the stock tree.
 */
struct stock_item *stock_init(const char *filename);

/**
 * \brief Save the stock tree to a status file.
 *
 * The status file has the same format as the one used in stock_init().
 * See the documentation of stock_init() for more details.
 *
 * \param root Root of the stock tree to save.
 * \param filename Name of the status file.
 * \return True if the save is successful, false otherwise.
 */
bool stock_save(struct stock_item *root, const char *filename);

#endif /* __STOCK_H__ */
