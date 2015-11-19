#include "../AppView.h"
#include "TextMode.h"

TextMode::TextMode(QGraphicsScene& scene, AppView& appView)
    : AbstractMode(scene),
      initialized_(false),
      appView_(appView),
      text_(0) {
    connect(&appView_, SIGNAL(toolChanged(ToolbarMode)),
            this, SLOT(clearFocus()));
}

void TextMode::init(int x, int y) {
    text_ = new QPlainTextEdit();
    text_->setStyleSheet("background: transparent; border: 0;");
    text_->move(x, y);
}

void TextMode::move(int x, int y) {
    if (initialized_) {
        return;
    }

    text_->move(x, y);
}

void TextMode::stop(int x, int y) {
    appView_.setMouseTracking(true);

    move(x, y);
    initialized_ = true;
    scene_.addWidget(text_);
    text_->setFocus();
}

void TextMode::clearFocus() {
    if (0 != text_) {
        text_->clearFocus();
    }
}
