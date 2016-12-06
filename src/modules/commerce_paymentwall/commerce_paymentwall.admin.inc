<?php

function commerce_paymentwall_configure()
{
    // Check Payment UI is enabled.
    if (!module_exists('commerce_payment_ui')) {
        drupal_set_message(t('The Payment UI module is disabled - please enable it before configuring Commerce paymentwall'), 'warning');
        drupal_goto('admin/modules');
        return;
    }

    // Load default payment rule configuration.
    $rule = rules_config_load('commerce_payment_commerce_paymentwall');
    if (empty($rule)) {
        drupal_set_message(t('The default payment rule configuration cannot be found'), 'warning');
        drupal_goto('admin/commerce/config/payment-methods');
        return;
    }

    // Check first action for default payment rule configuration.
    $action = $rule->actions()->current();
    if (empty($action)) {
        drupal_set_message(t('No actions exist for the default payment rule configuration'), 'warning');
        drupal_goto(
            sprintf(
                'admin/commerce/config/payment-methods/manage/%d',
                $rule->id
            )
        );
        return;
    }

    // Redirect user to configuration page.
    drupal_goto(
        sprintf(
            'admin/commerce/config/payment-methods/manage/%s/edit/%d',
            $rule->name,
            $action->elementId()
        )
    );
}

 
