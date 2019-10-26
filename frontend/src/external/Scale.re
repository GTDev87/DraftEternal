type t('a, 'b) = (('a) => 'b);

[@bs.module "@data-ui/radial-chart"] [@bs.val]
external singleHueScaleFactory : (string) => t('a, 'b) = "singleHueScaleFactory";
