#include "RuleWidget.hpp"

#include "base/Qv2rayBase.hpp"
#include "common/QvHelpers.hpp"

#define LOAD_FLAG_END isLoading = false;
#define LOAD_FLAG_BEGIN isLoading = true;
#define LOADINGCHECK                                                                                                                            \
    if (isLoading)                                                                                                                              \
        return;
#define rule (*ruleptr)

QvNodeRuleWidget::QvNodeRuleWidget(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
}

void QvNodeRuleWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange: retranslateUi(this); break;
        default: break;
    }
}

void QvNodeRuleWidget::ShowCurrentRuleDetail(std::shared_ptr<RuleObject> _ruleptr)
{
    LOADINGCHECK

    this->ruleptr = _ruleptr;

    // Switch to the detailed page.
    ruleEnableCB->setEnabled(true);
    ruleEnableCB->setChecked(rule.QV2RAY_RULE_ENABLED);
    ruleTagLineEdit->setEnabled(true);
    ruleRenameBtn->setEnabled(true);
    LOAD_FLAG_BEGIN
    ruleTagLineEdit->setText(rule.QV2RAY_RULE_TAG);
    //    balancerSelectionCombo->clear();

    //    for (auto out : outbounds)
    //    {
    //        balancerSelectionCombo->addItem(getTag(OUTBOUND(out)));
    //    }

    //    //
    //    // Balancers combo and balancer list.
    //    enableBalancerCB->setChecked(CurrentRule.QV2RAY_RULE_USE_BALANCER);
    //    balancersWidget->setEnabled(CurrentRule.QV2RAY_RULE_USE_BALANCER);

    //    if (!CurrentRule.balancerTag.isEmpty())
    //    {
    //        balancerList->clear();
    //        balancerList->addItems(balancers[CurrentRule.balancerTag]);
    //    }

    isLoading = false;
    // Networks
    auto network = rule.network.toLower();
    bool isBoth = (network.contains("tcp") && network.contains("udp")) || network.isEmpty();
    netUDPRB->setChecked(network.contains("udp"));
    netTCPRB->setChecked(network.contains("tcp"));
    netBothRB->setChecked(isBoth);
    //
    // Set protocol checkboxes.
    auto protocol = rule.protocol;
    routeProtocolHTTPCB->setChecked(protocol.contains("http"));
    routeProtocolTLSCB->setChecked(protocol.contains("tls"));
    routeProtocolBTCB->setChecked(protocol.contains("bittorrent"));
    //
    // Port
    routePortTxt->setText(rule.port);
    //
    // Users
    QString users = rule.user.join(NEWLINE);
    routeUserTxt->setPlainText(users);
    //
    // Incoming Sources
    QString sources = rule.source.join(NEWLINE);
    sourceIPList->setPlainText(sources);
    //
    // Domains
    QString domains = rule.domain.join(NEWLINE);
    hostList->setPlainText(domains);
    //
    // Outcoming IPs
    QString ips = rule.ip.join(NEWLINE);
    ipList->setPlainText(ips);
    LOAD_FLAG_END
}

void QvNodeRuleWidget::on_routeProtocolHTTPCB_stateChanged(int arg1)
{
    LOADINGCHECK
    QStringList protocols;

    if (arg1 == Qt::Checked)
        protocols.push_back("http");

    if (routeProtocolTLSCB->isChecked())
        protocols.push_back("tls");

    if (routeProtocolBTCB->isChecked())
        protocols.push_back("bittorrent");

    rule.protocol = protocols;
}
void QvNodeRuleWidget::on_routeProtocolTLSCB_stateChanged(int arg1)
{
    LOADINGCHECK
    QStringList protocols;

    if (arg1 == Qt::Checked)
        protocols.push_back("tls");

    if (routeProtocolHTTPCB->isChecked())
        protocols.push_back("http");

    if (routeProtocolBTCB->isChecked())
        protocols.push_back("bittorrent");

    rule.protocol = protocols;
}
void QvNodeRuleWidget::on_routeProtocolBTCB_stateChanged(int arg1)
{
    LOADINGCHECK
    QStringList protocols;

    if (arg1 == Qt::Checked)
        protocols.push_back("bittorrent");

    if (routeProtocolHTTPCB->isChecked())
        protocols.push_back("http");

    if (routeProtocolTLSCB->isChecked())
        protocols.push_back("tls");

    rule.protocol = protocols;
}
void QvNodeRuleWidget::on_hostList_textChanged()
{
    LOADINGCHECK
    rule.domain = SplitLines(hostList->toPlainText());
}
void QvNodeRuleWidget::on_ipList_textChanged()
{
    LOADINGCHECK
    rule.ip = SplitLines(ipList->toPlainText());
}
void QvNodeRuleWidget::on_routePortTxt_textEdited(const QString &arg1)
{
    LOADINGCHECK
    rule.port = arg1;
}
void QvNodeRuleWidget::on_routeUserTxt_textEdited(const QString &arg1)
{
    LOADINGCHECK
    rule.user = SplitLines(arg1);
}
void QvNodeRuleWidget::on_netBothRB_clicked()
{
    LOADINGCHECK
    rule.network = "tcp,udp";
}
void QvNodeRuleWidget::on_netUDPRB_clicked()
{
    LOADINGCHECK
    rule.network = "udp";
}
void QvNodeRuleWidget::on_netTCPRB_clicked()
{
    LOADINGCHECK
    rule.network = "tcp";
}
void QvNodeRuleWidget::on_routeUserTxt_textChanged()
{
    LOADINGCHECK
    rule.user = SplitLines(routeUserTxt->toPlainText());
}
void QvNodeRuleWidget::on_sourceIPList_textChanged()
{
    LOADINGCHECK
    rule.source = SplitLines(sourceIPList->toPlainText());
}
void QvNodeRuleWidget::on_enableBalancerCB_stateChanged(int arg1)
{
    //    LOADINGCHECK
    //    auto useBalancer = arg1 == Qt::Checked;
    //    CurrentRule.QV2RAY_RULE_USE_BALANCER = useBalancer;
    //    // balancersWidget->setEnabled(useBalancer);

    //    //    if (CurrentRule.balancerTag.isEmpty())
    //    //    {
    //    //        LOG(MODULE_UI, "Creating a new balancer tag.")
    //    //        CurrentRule.balancerTag = GenerateRandomString(6);
    //    //        balancers[CurrentRule.balancerTag] = QStringList();
    //    //    }

    //    DEBUG(MODULE_UI, "Balancer: " + CurrentRule.balancerTag)

    //    if (useBalancer)
    //    {
    //        LOG(MODULE_UI, "A rule has been set to use balancer, disconnect it to any outbound.")
    //        auto ruleNode = ruleNodes[currentRuleTag];
    //        for (auto &&[_, conn] : nodeScene->connections())
    //        {
    //            if (conn->getNode(PortType::Out)->id() == ruleNode)
    //            {
    //                nodeScene->deleteConnection(*conn);
    //                // Since there should be only one connection from this rule node.
    //                break;
    //            }
    //        }
    //    }
    //    else
    //    {
    //        QvMessageBoxWarn(this, tr("Route Editor"), tr("To make this rule ready to use, you need to connect it to an outbound node."));
    //    }
}
void QvNodeRuleWidget::on_ruleRenameBtn_clicked()
{
    abort();
    // auto newTag = ruleTagLineEdit->text();
    //
    // if (newTag.isEmpty())
    //{
    //    LOG(MODULE_UI, "Tag is empty, this is ILLEGAL!")
    //    QvMessageBoxWarn(this, tr("Renaming a tag"), tr("New tag is empty, please try another."));
    //}
    // else if (newTag == rule.QV2RAY_RULE_TAG)
    //{
    //    LOG(MODULE_UI, "No tag changed, returning.")
    //    QvMessageBoxInfo(this, tr("Renaming a tag"), tr("New tag is the same as the original one."));
    //}
    // else if (rules.contains(newTag))
    //{
    //    LOG(MODULE_UI, "Tag duplicate detected.")
    //    QvMessageBoxWarn(this, tr("Renaming a tag"), tr("Duplicate rule tag detected, please try another."));
    //}
    // else
    //{
    //    RenameItemTag(RENAME_RULE, rule.QV2RAY_RULE_TAG, &newTag);
    //}
}
void QvNodeRuleWidget::on_ruleEnableCB_stateChanged(int arg1)
{
    bool _isEnabled = arg1 == Qt::Checked;
    rule.QV2RAY_RULE_ENABLED = _isEnabled;
    settingsFrame->setEnabled(isEnabled());
}

void QvNodeRuleWidget::on_toolButton_clicked()
{
    settingsFrame->setVisible(!settingsFrame->isVisible());
    adjustSize();
}