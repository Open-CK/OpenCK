#ifndef CLEARABLELINEEDIT_H
#define CLEARABLELINEEDIT_H

#include <QLineEdit>

class QToolButton;
class ClearableLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	ClearableLineEdit(QWidget* parent = Q_NULLPTR);
	ClearableLineEdit(const ClearableLineEdit&) = default;
	ClearableLineEdit& operator=(const ClearableLineEdit&) = default;
	~ClearableLineEdit() = default;

protected:
	virtual void resizeEvent(QResizeEvent* ev) override;

private slots:
	void updateClearButton(const QString& text);

private:
	QToolButton* clearButton{ nullptr };
};

#endif