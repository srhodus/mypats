#include <QList>
#include <QStringList>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include "State.h"

State::State() {
    reserves.clear();
    foundations.clear();
    cascades.clear();
}

State::State(const QList<QStringList>& desc) {
	reserves.clear();
	foundations.clear();
	cascades.clear();
	for (int i = 0; i < Reserves.size(); i++) {
        reserves.append("");
	}
	for (int i = 0; i < Foundations.size(); i++) {
        foundations.append("");
	}
	for (int i = 0; i < desc.size(); i++) {
        QStringList sl;
		for (int j = 0; j < desc[i].size(); j++) {
			sl.append(desc[i][j]);
		}
        cascades.append(sl);
	}
}

QByteArray State::toJson() {
	QJsonArray reserveArray;
	for (const auto& i : reserves) {
		reserveArray.append(QJsonValue(i));
	}
	QJsonArray foundationArray;
	for (const auto& i : foundations) {
		foundationArray.append(QJsonValue(i));
	}
	QJsonObject jobj;
	jobj["reserves"] = reserveArray;
	jobj["foundations"] = foundationArray;
	QJsonArray cascadesArray;
	for (const auto& i : cascades) {
		QJsonArray ar;
		for (const auto& j : i) {
			ar.append(QJsonValue(j));
		}
		cascadesArray.append(ar);
	}
	jobj["cascades"] = cascadesArray;
	QJsonDocument doc(jobj);
	return doc.toJson(QJsonDocument::Compact);
}

bool State::fromJson(const QByteArray& ba) {
	QJsonDocument doc(QJsonDocument::fromJson(ba));
	if (!doc.isObject()) {
		qDebug() << "Error deserializing JSON document!";
		return false;
	}
	QJsonObject obj(doc.object());
	if (!obj.contains("reserves")) {
		qDebug() << "Error deserializing JSON document; missing `reserve`!";
		return false;
	}
	if (!obj.contains("foundations")) {
		qDebug() << "Error deserializing JSON document; missing `foundations`!";
		return false;
	}
	if (!obj.contains("cascades")) {
		qDebug() << "Error deserializing JSON document; missing `cascades`!";
		return false;
	}
	reserves.clear();
	for (const auto&& i : obj["reserves"].toArray()) {
		if (i.toString().isEmpty()) {
			reserves.append("");
		} else {
			reserves.append(i.toString());
		}
	}
	foundations.clear();
	for (const auto&& i : obj["foundations"].toArray()) {
		if (i.toString().isEmpty()) {
			foundations.append("");
		} else {
			foundations.append(i.toString());
		}
	}
	cascades.clear();
	for (const auto&& i : obj["cascades"].toArray()) {
        QStringList sl;
		for (const auto&& j : i.toArray()) {
			sl.append(j.toString());
		}
		cascades.append(sl);
	}
	return true;
}

QString State::toString() const {
	QString out;
	QString tmp;
	tmp.append("reserves: ");
	for (const auto& i : reserves) {
		if (i.isEmpty()) {
			tmp.append("--");
		} else {
			tmp.append(i);
		}
		tmp.append(" ");
	}
	out.append(tmp);
	out.append("\n");
	tmp.clear();
	tmp.append("foundations: ");
	for (const auto& i : foundations) {
		if (i.isEmpty()) {
			tmp.append("--");
		} else {
			tmp.append(i);
		}
		tmp.append(" ");
	}
	out.append(tmp);
	out.append("\n");
	for (const auto& i : cascades) {
		tmp.clear();
		for (const auto& j : i) {
			tmp.append(j);
			tmp.append(" ");
		}
		tmp = tmp.trimmed();
		out.append(tmp);
		out.append("\n");
	}
	return out;
}
