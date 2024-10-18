#pragma once

#include <fmt/base.h>
#include <fmt/format.h>

#include <QString>
#include <QVariant>

#include <string>


// fmtlib formatters for QString and QVariant

#define MAKE_FORMATTER(type, conversion)                                       \
    template <>                                                                \
    struct fmt::formatter<type, char> : fmt::formatter<std::string, char> {    \
        template <typename FmtContext>                                         \
        typename FmtContext::iterator format(const type &value, FmtContext &ctx) const \
        {                                                                      \
            return formatter<std::string, char>::format(conversion(value), ctx); \
        }                                                                      \
    }

auto QStringConversion = [](const QString &value) { return value.toStdString(); };
auto QVariantConversion = [](const QVariant &value) { return value.toString().toStdString(); };

MAKE_FORMATTER(QString,  QStringConversion);
MAKE_FORMATTER(QVariant, QVariantConversion);



