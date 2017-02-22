#ifndef DBUTIL_H
#define DBUTIL_H

#include <QMap>
#include <QList>
#include <QtSql>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>

/**
 * 本类封装了一些操作数据库的通用方法，例如插入、更新操作、查询结果返回整数，时间类型，
 * 还可以把查询结果映射成 map，甚至通过传入的映射函数把 map 映射成对象等，
 * 极大的简化了操作数据库的类的实现，参考 UserDao.cpp.
 *
 * sql 可以是一个简单的 SQL，如 SELECT id, username, password FROM user，
 * 也可以是一个需要绑定参数的 SQL，如 UPDATE user SET username=:username, password=:password WHERE id=:id，
 * 这时需要把要绑定的参数放在 map 里然后与 sql 一起作为参数传入，如
 *      QVariantMap params;
 *      params["id"]       = user.id;
 *      params["username"] = user.username;
 *      params["password"] = user.password;
 *
 *      DaoTemplate::update(sql, params);
 *
 * 所谓的 bean，就是一个简单的对象，只有属性[，getter 和 setter 方法]，主要目的是用来传输数据.
 *
 * 比较常用的方法有:
 *     insert
 *     update
 */

class DBUtil
{
public:
    /**
     * 执行插入语句，并返回插入行的 id.
     * @param sql
     * @param params
     * @return 如果执行成功返插入的记录的 id，否则返回 -1.
     */
    static int insert(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * 执行更新语句 (update 和 delete 语句都是更新语句).
     * @param sql
     * @param params
     * @return 如没有错误返回 true， 有错误返回 false.
     */
    static bool update(const QString &sql, const QVariantMap &params = QVariantMap());

 
    /**
     * 把 map 中的 key 和 value 绑定到 query 里.
     * @param query
     * @param params
     */
    static void bindValues(QSqlQuery *query, const QVariantMap &params);
public:
    static DBUtil *instance();
    static void releaseInstance();


    /**
     * 定义了访问数据库算法的骨架，SQL 语句执行的结果使用传进来的 Lambda 表达式处理
     * @param sql
     * @param params
     * @param fn - 处理 SQL 语句执行的结果的 Lambda 表达式
     */
    void executeSql(const QString &sql, const QVariantMap &params, std::function<void(QSqlQuery *query)> fn);

	QSqlDatabase db;
private:
    DBUtil();
    ~DBUtil();

private:

    static QMutex mutex;
    static DBUtil* s_Instance;
};

#endif // DBUTIL_H
